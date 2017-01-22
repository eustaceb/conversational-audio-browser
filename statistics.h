#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QMap>
#include <QPair>
#include <QStandardItemModel>

namespace Ui {
class Statistics;
}

class SelectionTreeModel;
class FilterTreeModel;
class Transcription;
class Speaker;
class Topic;
class Section;

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QMap<int, Transcription *> *transcriptions,
                        SelectionTreeModel *selectionTree, FilterTreeModel *filterTree,
                        QWidget *parent = 0);
    ~Statistics();

private slots:
    void generateGeneralModel();
private:
    Ui::Statistics *ui;

    QMap<int, Transcription *> *transcriptions;
    SelectionTreeModel *selectionTree;
    FilterTreeModel *filterTree;

    QStandardItemModel *generalModel;
    QMap<int, QStandardItemModel*> speakerModels, sectionModels, topicModels;

    void addTranscription(Transcription *t);
    void generateTranscriptionModels(Transcription *t);

    /*
     * Functions used for calculating stats
     */
    double median(const QList<double> &values) const;

    int turnCount(bool selected = false) const;
    int turnCount(Transcription *t, bool selected = false) const;
    int turnCount(Speaker *s, bool selected = false) const;
    int turnCount(Topic *t) const;
    int turnCount(Section *s) const;

    double turnLength(bool selected = false) const;
    double turnLength(Transcription *t, bool selected = false) const;
    double turnLength(Speaker *s, bool selected = false) const;
    double turnLength(Topic *t) const;
    double turnLength(Section *s) const;

    double medianTurnLength(bool selected = false) const;
    double medianTurnLength(Transcription *t) const;
    double medianTurnLength(Speaker *s) const;
    double medianTurnLength(Topic *t) const;
    double medianTurnLength(Section *s) const;

    double turnLengthVariance(bool selected = false) const;
    double turnLengthVariance(Transcription *t) const;
    double turnLengthVariance(Speaker *s) const;
    double turnLengthVariance(Topic *t) const;
    double turnLengthVariance(Section *s) const;

    QPair<double, double> turnLengthRange(bool selected = false) const;
    QPair<double, double> turnLengthRange(Transcription *t, bool selected = false) const;
    QPair<double, double> turnLengthRange(Speaker *s, bool selected = false) const;
    QPair<double, double> turnLengthRange(Topic *t) const;
    QPair<double, double> turnLengthRange(Section *s) const;

};

#endif // STATISTICS_H
