#include "statistics.h"
#include "ui_statistics.h"

#include "math.h"

#include "data-models/transcription.h"
#include "data-models/speaker.h"
#include "data-models/turn.h"

#include "trees/filtertreemodel.h"
#include "trees/filtertreeitem.h"
#include "trees/selectiontreemodel.h"
#include "trees/selectiontreeitem.h"

#include <QDebug>

Statistics::Statistics(QMap<int, Transcription *> *transcriptions,
                       SelectionTreeModel *selectionTree, FilterTreeModel *filterTree,
                       QWidget *parent) :
    transcriptions(transcriptions),
    selectionTree(selectionTree),
    filterTree(filterTree),
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    //ui->tabWidget->addTab()

    generalModel = new QStandardItemModel;
    generalModel->setHorizontalHeaderItem(0, new QStandardItem(QString("From")));
    generalModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Turn count")));
    generalModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Turn length")));
    generalModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Mean turn length")));
    generalModel->setHorizontalHeaderItem(4, new QStandardItem(QString("Turn len median")));
    generalModel->setHorizontalHeaderItem(5, new QStandardItem(QString("Turn len variance")));
    generalModel->setHorizontalHeaderItem(6, new QStandardItem(QString("Turn len stdev")));
    generalModel->setHorizontalHeaderItem(7, new QStandardItem(QString("Turn len range")));
    generalModel->setHorizontalHeaderItem(8, new QStandardItem(QString("Turn len skewness")));
    generalModel->setHorizontalHeaderItem(9, new QStandardItem(QString("No of overlaps")));
    generalModel->setHorizontalHeaderItem(10, new QStandardItem(QString("Len of overlaps")));
    generalModel->setHorizontalHeaderItem(11, new QStandardItem(QString("Overlap %")));

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
    // All
    generalModel->setItem(0, 0, new QStandardItem(QString("All")));
    generalModel->setItem(0, 1, new QStandardItem(QString::number(turnCount())));
    generalModel->setItem(0, 2, new QStandardItem(QString::number(turnLength())));
    generalModel->setItem(0, 3, new QStandardItem(QString::number(turnCount() == 0 ? 0 : turnLength() / turnCount())));
    generalModel->setItem(0, 4, new QStandardItem(QString::number(medianTurnLength())));
    double variance = turnLengthVariance();
    generalModel->setItem(0, 5, new QStandardItem(QString::number(variance)));
    generalModel->setItem(0, 6, new QStandardItem(QString::number(sqrt(variance))));
    QPair<double, double> range = turnLengthRange();
    QString rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
    generalModel->setItem(0, 7, new QStandardItem(rangeStr));

    // Selection
    int count = turnCount(true);
    double len = turnLength(true);
    generalModel->setItem(1, 0, new QStandardItem(QString("Selection")));
    generalModel->setItem(1, 1, new QStandardItem(QString::number(count)));
    generalModel->setItem(1, 2, new QStandardItem(QString::number(len)));
    generalModel->setItem(1, 3, new QStandardItem(QString::number(count == 0 ? 0 : len / count)));
    generalModel->setItem(1, 4, new QStandardItem(QString::number(medianTurnLength(true))));
    variance = turnLengthVariance(true);
    generalModel->setItem(1, 5, new QStandardItem(QString::number(variance)));
    generalModel->setItem(1, 6, new QStandardItem(QString::number(sqrt(variance))));
    range = turnLengthRange(true);
    rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
    generalModel->setItem(1, 7, new QStandardItem(rangeStr));
    // For each file
    int i = 2;
    foreach (Transcription *t, (*transcriptions)) {
        generalModel->setItem(i, 0, new QStandardItem(t->getFilename()));
        generalModel->setItem(i, 1, new QStandardItem(QString::number(turnCount(t))));
        generalModel->setItem(i, 2, new QStandardItem(QString::number(turnLength(t))));
        generalModel->setItem(i, 3, new QStandardItem(QString::number(turnCount(t) == 0 ? 0 : turnLength(t) / turnCount(t))));
        generalModel->setItem(i, 4, new QStandardItem(QString::number(medianTurnLength(t))));
        variance = turnLengthVariance(t);
        generalModel->setItem(i, 5, new QStandardItem(QString::number(variance)));
        generalModel->setItem(i, 6, new QStandardItem(QString::number(sqrt(variance))));
        range = turnLengthRange(t);
        rangeStr = "[" + QString::number(range.first) + "," + QString::number(range.second) + "]";
        generalModel->setItem(i, 7, new QStandardItem(rangeStr));
        i++;
    }
}

/*
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 * STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS STATS
 */
double Statistics::median(const QList<double> &values) const
{
    if (values.size() == 0) return nan("");
    double middle = values.at(values.size() / 2);
    if (values.size() % 2 != 0)
        return middle;
    else
        return (middle + values.at(values.size() / 2 - 1)) / 2;
}

int Statistics::turnCount(bool selected) const
{
    int count = 0;
    foreach (Transcription *t, (*transcriptions)) {
        count += turnCount(t, selected);
    }
    return count;
}

int Statistics::turnCount(Transcription *t, bool selected) const
{
    int count = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        count += turnCount(s, selected);
    }
    return count;
}

int Statistics::turnCount(Speaker *s, bool selected) const
{
    if (!selected) return s->getTurns().length();
    int count = 0;
    foreach (Turn *trn, s->getTurns()) {
        if (trn->isSelected() && s->isFiltered())
            count++;
    }
    return count;
}

double Statistics::turnLength(bool selected) const
{
    double len = 0;
    foreach (Transcription *t, (*transcriptions)) {
        len += turnLength(t, selected);
    }
    return len;
}

double Statistics::turnLength(Transcription *t, bool selected) const
{
    double len = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        len += turnLength(s, selected);
    }
    return len;
}

double Statistics::turnLength(Speaker *s, bool selected) const
{
    if (selected && !s->isFiltered()) return 0;
    if (!selected) return s->getTotalTurnLength();

    double len = 0;
    foreach (Turn *trn, s->getTurns())
            if (trn->isSelected())
                len += trn->getDuration();
    return len;
}


double Statistics::medianTurnLength(bool selected) const
{
    QMultiMap<double, bool> turnLengths;
    foreach (Transcription *t, (*transcriptions)) {
        foreach (Speaker *s, t->getSpeakers()) {
            if (selected && !s->isFiltered()) continue;
            foreach (Turn *trn, s->getTurns()) {
                if (!selected || trn->isSelected())
                    turnLengths.insert(trn->getDuration(), true);
            }
        }
    }
    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Transcription *t) const
{
    QMultiMap<double, bool> turnLengths;

    foreach (Speaker *s, t->getSpeakers())
        foreach (Turn *trn, s->getTurns())
            turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::medianTurnLength(Speaker *s) const
{
    QMultiMap<double, bool> turnLengths;

    foreach (Turn *trn, s->getTurns())
        turnLengths.insert(trn->getDuration(), true);

    return median(turnLengths.keys());
}

double Statistics::turnLengthVariance(bool selected) const
{
    int count = turnCount(selected);
    double mean = turnLength(selected) / count;
    double squaredDiff = 0;

    foreach (Transcription *t, (*transcriptions)) {
        foreach (Speaker *s, t->getSpeakers()) {
            if (selected && !s->isFiltered()) continue;
            foreach (Turn *trn, s->getTurns()) {
                if (!selected || trn->isSelected())
                    squaredDiff += pow((trn->getDuration() - mean), 2);
            }
        }
    }

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Transcription *t) const
{
    int count = turnCount(t);
    double squaredDiff = 0;
    double mean = turnLength(t) / count;

    foreach (Speaker *s, t->getSpeakers())
        foreach (Turn *trn, s->getTurns())
            squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

double Statistics::turnLengthVariance(Speaker *s) const
{
    int count = turnCount(s);
    double squaredDiff = 0;
    double mean = turnLength(s) / count;

    foreach (Turn *trn, s->getTurns())
        squaredDiff += pow((trn->getDuration() - mean), 2);

    return squaredDiff / count;
}

QPair<double, double> Statistics::turnLengthRange(bool selected) const
{
    double min = 0, max = 0;
    foreach (Transcription *t, (*transcriptions)) {
        QPair<double, double> p = turnLengthRange(t, selected);
        if (min == 0 || p.first < min)
            min = p.first;
        if (p.second > max)
            max = p.second;
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Transcription *t, bool selected) const
{
    double min = 0, max = 0;
    foreach (Speaker *s, t->getSpeakers()) {
        QPair<double, double> p = turnLengthRange(s, selected);
        if (min == 0 || p.first < min)
            min = p.first;
        if (p.second > max)
            max = p.second;
    }
    return QPair<double, double>(min, max);
}

QPair<double, double> Statistics::turnLengthRange(Speaker *s, bool selected) const
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
