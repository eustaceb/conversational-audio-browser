#include "statistics.h"
#include "ui_statistics.h"

#include "math.h"

#include "helpers.h"
#include "data-models/transcription.h"
#include "data-models/speaker.h"
#include "data-models/turn.h"
#include "data-models/topic.h"
#include "data-models/section.h"

#include "trees/filtertreemodel.h"
#include "trees/filtertreeitem.h"
#include "trees/selectiontreemodel.h"
#include "trees/selectiontreeitem.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

Statistics::Statistics(QMap<int, Transcription *> *transcriptions, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics),
    transcriptions(transcriptions)
{
    ui->setupUi(this);
    //ui->tabWidget->addTab()

    generalModel = new QStandardItemModel;

    generateGeneralModel();

    ui->generalTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->generalTableView->setModel(generalModel);
}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::generateGeneralModel()
{
    generalModel->clear();
    //generalModel->
    QStringList labels(QList<QString>() << "From" << "Turn Count" << "Total turn length" <<
                       "Mean turn length" << "Turn length median" << "Turn length variance" <<
                       "Turn length stdev" << "Turn length skewness" << "Turn length range");
                       //"No of overlaps" << "Len of overlaps" << "Overlap %");
    generalModel->setHorizontalHeaderLabels(labels);
    // All
    generalModel->setItem(0, 0, new QStandardItem(QString("All")));
    int turnCountAll = turnCount(transcriptions);
    double turnLenAll = turnLength(transcriptions);
    generalModel->setItem(0, 1, new QStandardItem(QString::number(turnCountAll)));
    generalModel->setItem(0, 2, new QStandardItem(QString::number(turnLenAll)));
    generalModel->setItem(0, 3, new QStandardItem(QString::number(turnCountAll == 0 ? 0 : turnLenAll / turnCountAll)));
    generalModel->setItem(0, 4, new QStandardItem(QString::number(medianTurnLength(transcriptions))));
    double variance = turnLengthVariance(transcriptions);
    generalModel->setItem(0, 5, new QStandardItem(QString::number(variance)));
    generalModel->setItem(0, 6, new QStandardItem(QString::number(sqrt(variance))));
    generalModel->setItem(0, 7, new QStandardItem(QString::number(turnLengthSkewness(transcriptions))));
    QPair<double, double> range = turnLengthRange(transcriptions);
    QString rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
    generalModel->setItem(0, 8, new QStandardItem(rangeStr));

    // Selection
    int count = turnCount(transcriptions, true);
    double len = turnLength(transcriptions, true);
    generalModel->setItem(1, 0, new QStandardItem(QString("Selection")));
    generalModel->setItem(1, 1, new QStandardItem(QString::number(count)));
    generalModel->setItem(1, 2, new QStandardItem(QString::number(len)));
    generalModel->setItem(1, 3, new QStandardItem(QString::number(count == 0 ? 0 : len / count)));
    generalModel->setItem(1, 4, new QStandardItem(QString::number(medianTurnLength(transcriptions, true))));
    variance = turnLengthVariance(transcriptions, true);
    generalModel->setItem(1, 5, new QStandardItem(QString::number(variance)));
    generalModel->setItem(1, 6, new QStandardItem(QString::number(sqrt(variance))));
    generalModel->setItem(1, 7, new QStandardItem(QString::number(turnLengthSkewness(transcriptions, true))));
    range = turnLengthRange(transcriptions, true);
    rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
    generalModel->setItem(1, 8, new QStandardItem(rangeStr));
    // For each file
    int i = 2;
    foreach (Transcription *t, (*transcriptions)) {
        // If the transcription is not registered - skip
        // happens when a transcription is pending removal
        if (!speakerModels.contains(t->getId())) continue;

        generalModel->setItem(i, 0, new QStandardItem(t->getFilename()));
        generalModel->setItem(i, 1, new QStandardItem(QString::number(turnCount(t))));
        generalModel->setItem(i, 2, new QStandardItem(QString::number(turnLength(t))));
        generalModel->setItem(i, 3, new QStandardItem(QString::number(turnCount(t) == 0 ? 0 : turnLength(t) / turnCount(t))));
        generalModel->setItem(i, 4, new QStandardItem(QString::number(medianTurnLength(t))));
        variance = turnLengthVariance(t);
        generalModel->setItem(i, 5, new QStandardItem(QString::number(variance)));
        generalModel->setItem(i, 6, new QStandardItem(QString::number(sqrt(variance))));
        generalModel->setItem(i, 7, new QStandardItem(QString::number(turnLengthSkewness(t))));
        range = turnLengthRange(t);
        rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
        generalModel->setItem(i, 8, new QStandardItem(rangeStr));
        i++;
    }
    ui->generalTableView->setSortingEnabled(true);
    ui->generalTableView->resizeColumnsToContents();
}

void Statistics::addTranscription(Transcription *t)
{
    // Prevent from double-adding. Checking just one of the maps is sufficient.
    if (speakerModels.contains(t->getId())) return;

    // First, generate item models (empty tables)

    QStandardItemModel *speakerModel = new QStandardItemModel;
    QStringList labels(QList<QString>() << "Speaker" << "Turn Count" << "Total turn length" <<
                       "Mean turn length" << "Turn length median" << "Turn length variance" <<
                       "Turn length stdev" << "Turn length skewness" << "Turn length range");
                       //"No of overlaps" << "Len of overlaps" << "Overlap %");
    speakerModel->setHorizontalHeaderLabels(labels);
    speakerModels.insert(t->getId(), speakerModel);

    QStandardItemModel *topicModel = new QStandardItemModel;
    labels = QStringList(QList<QString>() << "Topic" << "Turn Count" << "Total turn length" <<
                       "Mean turn length" << "Turn length median" << "Turn length variance" <<
                       "Turn length stdev" << "Turn length skewness" << "Turn length range");
                       //"No of overlaps" << "Len of overlaps" << "Overlap %");
    topicModel->setHorizontalHeaderLabels(labels);
    topicModels.insert(t->getId(), topicModel);

    QStandardItemModel *sectionModel = new QStandardItemModel;
    labels = QStringList(QList<QString>() << "Section" << "Turn Count" << "Turn length" <<
                       "Mean turn length" << "Turn length median" << "Turn length variance" <<
                       "Turn length stdev" << "Turn length skewness" << "Turn length range");
                       //"No of overlaps" << "Len of overlaps" << "Overlap %");
    sectionModel->setHorizontalHeaderLabels(labels);
    sectionModels.insert(t->getId(), sectionModel);

    // Generate content
    generateTranscriptionModels(t);

    // Create UI elements for tab
    QWidget *w = new QWidget;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(new QLabel("Speakers"));
    QTableView *speakerTable = new QTableView;
    speakerTable->setModel(speakerModel);
    speakerTable->setSortingEnabled(true);
    speakerTable->resizeColumnsToContents();
    speakerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalLayout->addWidget(speakerTable);
    verticalLayout->addWidget(new QLabel("Topics"));
    QTableView *topicTable = new QTableView;
    topicTable->setModel(topicModel);
    topicTable->setSortingEnabled(true);
    topicTable->resizeColumnsToContents();
    topicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalLayout->addWidget(topicTable);
    verticalLayout->addWidget(new QLabel("Sections"));
    QTableView *sectionTable = new QTableView;
    sectionTable->setModel(sectionModel);
    sectionTable->setSortingEnabled(true);
    sectionTable->resizeColumnsToContents();
    sectionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalLayout->addWidget(sectionTable);

    w->setLayout(verticalLayout);

    ui->tabWidget->addTab(w, t->getFilename()); // add tab
    pageToTranscriptionId.insert(ui->tabWidget->indexOf(w), t->getId()); // associate tab page id with trs id
    generateGeneralModel(); // regenerate general model
}

void Statistics::removeTranscription(Transcription *t)
{
    topicModels.remove(t->getId());
    sectionModels.remove(t->getId());
    speakerModels.remove(t->getId());

    ui->tabWidget->removeTab(pageToTranscriptionId.key(t->getId()));

    generateGeneralModel();
}

void Statistics::generateTranscriptionModels(Transcription *t)
{
    // Speaker model
    QStandardItemModel *speakerModel = speakerModels.find(t->getId()).value();
    int i = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        speakerModel->setItem(i, 0, new QStandardItem(s->getName()));
        speakerModel->setItem(i, 1, new QStandardItem(QString::number(turnCount(s))));
        speakerModel->setItem(i, 2, new QStandardItem(QString::number(turnLength(s))));
        speakerModel->setItem(i, 3, new QStandardItem(QString::number(turnCount(s) == 0 ? 0 : turnLength(s) / turnCount(s))));
        speakerModel->setItem(i, 4, new QStandardItem(QString::number(medianTurnLength(s))));
        double variance = turnLengthVariance(s);
        speakerModel->setItem(i, 5, new QStandardItem(QString::number(variance)));
        speakerModel->setItem(i, 6, new QStandardItem(QString::number(sqrt(variance))));
        speakerModel->setItem(i, 7, new QStandardItem(QString::number(turnLengthSkewness(s))));
        QPair<double, double> range = turnLengthRange(s);
        QString rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
        speakerModel->setItem(i, 8, new QStandardItem(rangeStr));
        i++;
    }
    // Topic and section models
    QStandardItemModel *topicModel = topicModels.find(t->getId()).value();
    QStandardItemModel *sectionModel = sectionModels.find(t->getId()).value();
    i = 0;
    int j = 0;
    foreach (Topic *to, t->getTopics()) {
        foreach (Section *s, to->getSections()) {
            sectionModel->setItem(j, 0, new QStandardItem(QString::number(s->getId()) + " - " + to->getDesc()));
            sectionModel->setItem(j, 1, new QStandardItem(QString::number(turnCount(s))));
            sectionModel->setItem(j, 2, new QStandardItem(QString::number(turnLength(s))));
            sectionModel->setItem(j, 3, new QStandardItem(QString::number(turnCount(s) == 0 ? 0 : turnLength(s) / turnCount(s))));
            sectionModel->setItem(j, 4, new QStandardItem(QString::number(medianTurnLength(s))));
            double variance = turnLengthVariance(s);
            sectionModel->setItem(j, 5, new QStandardItem(QString::number(variance)));
            sectionModel->setItem(j, 6, new QStandardItem(QString::number(sqrt(variance))));
            sectionModel->setItem(i, 7, new QStandardItem(QString::number(turnLengthSkewness(s))));
            QPair<double, double> range = turnLengthRange(s);
            QString rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
            sectionModel->setItem(j, 8, new QStandardItem(rangeStr));
            j++;
        }
        topicModel->setItem(i, 0, new QStandardItem(to->getDesc()));
        topicModel->setItem(i, 1, new QStandardItem(QString::number(turnCount(to))));
        topicModel->setItem(i, 2, new QStandardItem(QString::number(turnLength(to))));
        topicModel->setItem(i, 3, new QStandardItem(QString::number(turnCount(to) == 0 ? 0 : turnLength(to) / turnCount(to))));
        topicModel->setItem(i, 4, new QStandardItem(QString::number(medianTurnLength(to))));
        double variance = turnLengthVariance(to);
        topicModel->setItem(i, 5, new QStandardItem(QString::number(variance)));
        topicModel->setItem(i, 6, new QStandardItem(QString::number(sqrt(variance))));
        topicModel->setItem(i, 7, new QStandardItem(QString::number(turnLengthSkewness(to))));
        QPair<double, double> range = turnLengthRange(to);
        QString rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
        topicModel->setItem(i, 8, new QStandardItem(rangeStr));
        i++;
    }
}

/*
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 */
double Statistics::median(const QList<double> &values)
{
    if (values.size() == 0) return nan("");
    double middle = values.at(values.size() / 2);
    if (values.size() % 2 != 0)
        return middle;
    else
        return (middle + values.at(values.size() / 2 - 1)) / 2;
}

int Statistics::turnCount(QMap<int, Transcription *> *transcriptions, bool selected)
{
    int count = 0;
    foreach (Transcription *t, (*transcriptions)) {
        count += t->getTurnList(selected).size();
    }
    return count;
}

int Statistics::turnCount(Transcription *t, bool selected)
{
    return t->getTurnList(selected).count();
}

int Statistics::turnCount(Speaker *s, bool selected)
{
    if (!selected) return s->getTurns().length();
    int count = 0;
    foreach (Turn *trn, s->getTurns()) {
        if (trn->isSelected() && s->isFiltered())
            count++;
    }
    return count;
}

int Statistics::turnCount(Topic *t)
{
    int count = 0;
    foreach (Section *s, t->getSections())
        count += turnCount(s);
    return count;
}

int Statistics::turnCount(Section *s)
{
    return s->getTurns().length();
}

double Statistics::turnLength(QMap<int, Transcription *> *transcriptions, bool selected)
{
    double len = 0;
    foreach (Transcription *t, (*transcriptions)) {
        len += turnLength(t, selected);
    }
    return len;
}

double Statistics::turnLength(Transcription *t, bool selected)
{
    double len = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        len += turnLength(s, selected);
    }
    return len;
}

double Statistics::turnLength(Speaker *s, bool selected)
{
    if (selected && !s->isFiltered()) return 0;

    double len = 0;
    foreach (Turn *trn, s->getTurns())
            if (!selected || trn->isSelected())
                len += trn->getDuration();
    return len;
}

double Statistics::turnLength(Topic *t)
{
    double len = 0;
    foreach (Section *s, t->getSections())
        len += turnLength(s);
    return len;
}

double Statistics::turnLength(Section *s)
{
    double len = 0;
    foreach (Turn *t, s->getTurns())
        len += t->getDuration();
    return len;
}

double Statistics::medianTurnLength(QMap<int, Transcription *> *transcriptions, bool selected)
{
    QMultiMap<double, bool> turnLengths;
    foreach (Transcription *t, (*transcriptions))
        foreach (Turn *trn, t->getTurnList(selected))
            turnLengths.insert(trn->getDuration(), true);
    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Transcription *t)
{
    QMultiMap<double, bool> turnLengths;

    foreach (Speaker *s, t->getSpeakers())
        foreach (Turn *trn, s->getTurns())
            turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Speaker *s)
{
    QMultiMap<double, bool> turnLengths;

    foreach (Turn *trn, s->getTurns())
        turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Topic *t)
{
    QMultiMap<double, bool> turnLengths;

    foreach (Section *s, t->getSections())
        foreach (Turn *trn, s->getTurns())
            turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Section *s)
{
    QMultiMap<double, bool> turnLengths;

    foreach (Turn *trn, s->getTurns())
        turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::turnLengthVariance(QMap<int, Transcription *> *transcriptions, bool selected)
{
    int count = turnCount(transcriptions, selected);
    double mean = turnLength(transcriptions, selected) / count;
    double squaredDiff = 0;

    foreach (Transcription *t, (*transcriptions))
        foreach (Turn *trn, t->getTurnList(selected))
                squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Transcription *t)
{
    int count = turnCount(t);
    double squaredDiff = 0;
    double mean = turnLength(t) / count;

    foreach (Speaker *s, t->getSpeakers())
        foreach (Turn *trn, s->getTurns())
            squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Speaker *s)
{
    int count = turnCount(s);
    double squaredDiff = 0;
    double mean = turnLength(s) / count;

    foreach (Turn *trn, s->getTurns())
        squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Topic *t)
{
    int count = turnCount(t);
    double squaredDiff = 0;
    double mean = turnLength(t) / count;

    foreach (Section *s, t->getSections())
        foreach (Turn *trn, s->getTurns())
            squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Section *s)
{
    int count = turnCount(s);
    double squaredDiff = 0;
    double mean = turnLength(s) / count;

    foreach (Turn *trn, s->getTurns())
        squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthSkewness(QMap<int, Transcription *> *transcriptions, bool selected)
{
    double mean = turnLength(transcriptions, selected) / turnCount(transcriptions, selected);
    return 3 * (mean - medianTurnLength(transcriptions, selected)) / sqrt(turnLengthVariance(transcriptions, selected));
}

double Statistics::turnLengthSkewness(Transcription *t)
{
    double mean = turnLength(t) / turnCount(t);
    return 3 * (mean - medianTurnLength(t)) / sqrt(turnLengthVariance(t));
}

double Statistics::turnLengthSkewness(Speaker *s)
{
    double mean = turnLength(s) / turnCount(s);
    return 3 * (mean - medianTurnLength(s)) / sqrt(turnLengthVariance(s));
}

double Statistics::turnLengthSkewness(Topic *t)
{
    double mean = turnLength(t) / turnCount(t);
    return 3 * (mean - medianTurnLength(t)) / sqrt(turnLengthVariance(t));
}

double Statistics::turnLengthSkewness(Section *s)
{
    double mean = turnLength(s) / turnCount(s);
    return 3 * (mean - medianTurnLength(s)) / sqrt(turnLengthVariance(s));
}
/*
QList<double> Statistics::getOverlaps(bool selected)
{
    QList<double> result;
    foreach (Transcription *t, (*transcriptions))
        result.append(getOverlaps(t, selected));
    return result;
}

QList<double> Statistics::getOverlaps(Transcription *t, bool selected)
{
    QList<double> result;
    // We're going to need a list of pairs sorted by the first element
    // Not single doubles so we keep track of what are the bounds of the interval
    QMap<QPair<double, double>, int> intervalMap;
    foreach (Turn *trn, t->getTurnList(selected)) {
        if (!intervalMap.contains(QPair<double, double>(trn->getEndTime(), trn->getStartTime()))) {
            intervalMap.insert(QPair<double, double>(trn->getStartTime(), trn->getEndTime()), 1);
            intervalMap.insert(QPair<double, double>(trn->getEndTime(), trn->getStartTime()), 1);
        } else {
            intervalMap[QPair<double, double>(trn->getEndTime(), trn->getStartTime())]++;
        }
    }
    // TODO: custom comparator required; ties - end points before start points
    QList<QPair<double, double>> intervals = intervalMap.keys();
    std::sort(intervals.begin(), intervals.end());

    QList<QPair<double, double>> currentlyOpen;
    for (int i = 0; i < intervals.size(); i++) {
        QPair<double, double> now = intervals.at(i);
        if (now.first > now.second) { // interval opens
            currentlyOpen.add(now);
        } else {
            int r = 0;
            for (int j = 0; j < currentlyOpen.size(); j++) {
                QPair<double, double> openPair = currentlyOpen.at(j);
                if (openPair.first == now.second && openPair.second == now.first) {
                    int intervalCount = intervalMap.find(now).value()
                    r = j;
                } else {
                    // Account for duplicates - multiply the overlaps by the amount of identical intervals
                    //if (duplicates.)
                }
            }
            currentlyOpen.removeAt(r);
        }
    }

}*/

QPair<double, double> Statistics::turnLengthRange(QMap<int, Transcription *> *transcriptions, bool selected)
{
    double min = 0, max = 0;
    foreach (Transcription *t, (*transcriptions)) {
        QPair<double, double> p = turnLengthRange(t, selected);
        if (min == 0 || (p.first < min && p.first != 0))
            min = p.first;
        if (p.second > max)
            max = p.second;
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Transcription *t, bool selected)
{
    double min = 0, max = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        QPair<double, double> p = turnLengthRange(s, selected);
        if (min == 0 || (p.first < min && p.first != 0))
            min = p.first;
        if (p.second > max)
            max = p.second;
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Speaker *s, bool selected)
{
    if (selected && !s->isFiltered()) return QPair<double, double>(0, 0);
    double min = 0, max = 0;
    foreach (Turn *t, s->getTurns()) {
        if (!selected || t->isSelected()) {
            if (min == 0 || t->getDuration() < min)
                min = t->getDuration();
            if (t->getDuration() > max)
                max = t->getDuration();
        }
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Topic *t)
{
    double min = 0, max = 0;
    foreach (Section *s, t->getSections()) {
        QPair<double, double> p = turnLengthRange(s);
        if (min == 0 || (p.first < min && p.first != 0))
            min = p.first;
        if (p.second > max)
            max = p.second;
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Section *s)
{
    double min = 0, max = 0;
    foreach (Turn *t, s->getTurns()) {
            if (min == 0 || t->getDuration() < min)
                min = t->getDuration();
            if (t->getDuration() > max)
                max = t->getDuration();
    }
    return QPair<double, double>(min, max);
}

void Statistics::on_exportButton_clicked()
{
    bool success = true, headers = ui->headersCheckBox->checkState() == Qt::Checked;

    if (ui->tabWidget->currentIndex() != 0) {
        int trsId = pageToTranscriptionId.find(ui->tabWidget->currentIndex()).value();
        QString prefix = QFileDialog::getSaveFileName(this, "Select prefix and location for exported files", "/", "Any (*.*)");
        if (prefix == "") return;
        QString fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-speakers.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, speakerModels.find(trsId).value(), headers) == 1;
        fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-sections.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, sectionModels.find(trsId).value(), headers) == 1;
        fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-topics.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, topicModels.find(trsId).value(), headers) == 1;
    } else {
        QString generalFile = QFileDialog::getSaveFileName(this, "General statistics", "/", "Comma-Seperated Values (*.csv)");
        if (generalFile == "") return;
        if (generalFile.split(".").last() != "csv")
            generalFile += ".csv";
        success &= Helpers::exportStdItemModelToCsv(generalFile, generalModel, headers) == 1;
    }

    QMessageBox msgBox;
    if (success) {
        msgBox.setText("File(s) have been successfully exported.");
        msgBox.setIcon(QMessageBox::Information);
    } else {
        msgBox.setText("Something went wrong.");
        msgBox.setIcon(QMessageBox::Critical);
    }
    msgBox.exec();
}

void Statistics::on_exportAllButton_clicked()
{
    QMessageBox msgBox;
    bool success = true, headers = ui->headersCheckBox->checkState() == Qt::Checked;

    QString prefix = QFileDialog::getSaveFileName(this, "Select prefix and location for exported files", "/", "Any (*.*)");
    if (prefix == "") return;
    QString fileName = prefix + "-general.csv";
    success &= Helpers::exportStdItemModelToCsv(fileName, generalModel, headers) == 1;

    foreach (int trsId, pageToTranscriptionId) {
        QString fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-speakers.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, speakerModels.find(trsId).value(), headers) == 1;
        fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-sections.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, sectionModels.find(trsId).value(), headers) == 1;
        fileName = prefix + "-" + transcriptions->find(trsId).value()->getTitle() + "-topics.csv";
        success &= Helpers::exportStdItemModelToCsv(fileName, topicModels.find(trsId).value(), headers) == 1;
    }

    if (success) {
        msgBox.setText("File(s) have been successfully exported.");
        msgBox.setIcon(QMessageBox::Information);
    } else {
        msgBox.setText("Something went wrong.");
        msgBox.setIcon(QMessageBox::Critical);
    }
    msgBox.exec();
}
