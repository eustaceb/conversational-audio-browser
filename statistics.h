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
    static qreal median(QList<qreal> values);

    static int turnCount(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static int turnCount(Transcription *t, bool selected = false);
    static int turnCount(Speaker *s, bool selected = false);
    static int turnCount(Topic *t);
    static int turnCount(Section *s);

    static qreal turnLength(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static qreal turnLength(Transcription *t, bool selected = false);
    static qreal turnLength(Speaker *s, bool selected = false);
    static qreal turnLength(Topic *t);
    static qreal turnLength(Section *s);

    static qreal medianTurnLength(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static qreal medianTurnLength(Transcription *t);
    static qreal medianTurnLength(Speaker *s);
    static qreal medianTurnLength(Topic *t);
    static qreal medianTurnLength(Section *s);

    static qreal turnLengthVariance(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static qreal turnLengthVariance(Transcription *t);
    static qreal turnLengthVariance(Speaker *s);
    static qreal turnLengthVariance(Topic *t);
    static qreal turnLengthVariance(Section *s);

    static qreal turnLengthSkewness(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static qreal turnLengthSkewness(Transcription *t);
    static qreal turnLengthSkewness(Speaker *s);
    static qreal turnLengthSkewness(Topic *t);
    static qreal turnLengthSkewness(Section *s);
/*
    QList<qreal> getOverlaps(bool selected = false);
    QList<qreal> getOverlaps(Transcription *t, bool selected = false);
    QList<qreal> getOverlaps(Speaker *s);
    QList<qreal> getOverlaps(Topic *t);
    QList<qreal> getOverlaps(Section *s);

    qreal overlapLength(bool selected = false);
    qreal overlapLength(Transcription *t);
    qreal overlapLength(Speaker *s);
    qreal overlapLength(Topic *t);
    qreal overlapLength(Section *s);
*/
    static QPair<qreal, qreal> turnLengthRange(QMap<int, Transcription *> *transcriptions, bool selected = false);
    static QPair<qreal, qreal> turnLengthRange(Transcription *t, bool selected = false);
    static QPair<qreal, qreal> turnLengthRange(Speaker *s, bool selected = false);
    static QPair<qreal, qreal> turnLengthRange(Topic *t);
    static QPair<qreal, qreal> turnLengthRange(Section *s);

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
