#ifndef TESTSTATISTICS_H
#define TESTSTATISTICS_H

#include <QObject>
#include <QTest>

class Transcription;

class TestStatistics : public QObject
{
    Q_OBJECT
private:
    Transcription *t1, *t2;
private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();
};

#endif // TESTSTATISTICS_H
