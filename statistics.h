#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QMap>
#include <QHash>
#include <QPair>
#include <QStandardItemModel>

namespace Ui {
class Statistics;
}

class Transcription;
class Speaker;
class Topic;
class Section;

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QMap<int, Transcription *> *transcriptions,
                        QWidget *parent = 0);
    ~Statistics();

    void addTranscription(Transcription *t);
    void removeTranscription(Transcription *t);

    /*
     * Functions used for calculating stats
     */
    static double median(const QList<double> &values);

    static int turnCount(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static int turnCount(Transcription *t, bool selected = false);
    static int turnCount(Speaker *s, bool selected = false);
    static int turnCount(Topic *t);
    static int turnCount(Section *s);

    static double turnLength(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static double turnLength(Transcription *t, bool selected = false);
    static double turnLength(Speaker *s, bool selected = false);
    static double turnLength(Topic *t);
    static double turnLength(Section *s);

    static double medianTurnLength(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static double medianTurnLength(Transcription *t);
    static double medianTurnLength(Speaker *s);
    static double medianTurnLength(Topic *t);
    static double medianTurnLength(Section *s);

    static double turnLengthVariance(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static double turnLengthVariance(Transcription *t);
    static double turnLengthVariance(Speaker *s);
    static double turnLengthVariance(Topic *t);
    static double turnLengthVariance(Section *s);

    static double turnLengthSkewness(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static double turnLengthSkewness(Transcription *t);
    static double turnLengthSkewness(Speaker *s);
    static double turnLengthSkewness(Topic *t);
    static double turnLengthSkewness(Section *s);
/*
    QList<double> getOverlaps(bool selected = false);
    QList<double> getOverlaps(Transcription *t, bool selected = false);
    QList<double> getOverlaps(Speaker *s);
    QList<double> getOverlaps(Topic *t);
    QList<double> getOverlaps(Section *s);

    double overlapLength(bool selected = false);
    double overlapLength(Transcription *t);
    double overlapLength(Speaker *s);
    double overlapLength(Topic *t);
    double overlapLength(Section *s);
*/
    static QPair<double, double> turnLengthRange(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static QPair<double, double> turnLengthRange(Transcription *t, bool selected = false);
    static QPair<double, double> turnLengthRange(Speaker *s, bool selected = false);
    static QPair<double, double> turnLengthRange(Topic *t);
    static QPair<double, double> turnLengthRange(Section *s);

private slots:
    void generateGeneralModel();

    void on_exportButton_clicked();

    void on_exportAllButton_clicked();

private:
    Ui::Statistics *ui;

    QMap<int, Transcription *> *transcriptions;

    QStandardItemModel *generalModel;
    QMap<int, QStandardItemModel*> speakerModels, sectionModels, topicModels;
    QHash<int, int>  pageToTranscriptionId;

    void generateTranscriptionModels(Transcription *t);

};

#endif // STATISTICS_H
