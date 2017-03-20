#ifndef TESTDATAMODELS_H
#define TESTDATAMODELS_H

#include <QObject>
#include <QtTest/QtTest>

class Transcription;

class TestDataModels : public QObject
{
    Q_OBJECT
private slots:

    void testTranscription();
    void testTopic();
    void testSection();
    void testTurn();
    void testSpeaker();
};

#endif // TESTDATAMODELS_H
