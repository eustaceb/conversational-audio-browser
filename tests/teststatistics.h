#ifndef TESTSTATISTICS_H
#define TESTSTATISTICS_H

#include <QObject>
#include <QtTest/QtTest>

class Transcription;

class TestStatistics : public QObject
{
    Q_OBJECT
private:
    Transcription *trs;
    bool areRealsEqual(qreal actual, qreal expected, qreal epsilon = 0.00001);
private slots:
    void initTestCase();
    void cleanupTestCase();

    void testMedian();
    void testTurnCount();
    void testTurnLength();
    void testMedianTurnLength();
    void testTurnLengthVariance();
    void testTurnLengthSkewness();
    void testTurnLengthRange();
};

#endif // TESTSTATISTICS_H
