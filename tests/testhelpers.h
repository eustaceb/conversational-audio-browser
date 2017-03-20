#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <QObject>
#include <QtTest/QtTest>

class TestHelpers : public QObject
{
    Q_OBJECT

private slots:
    void testParseTranscription();
};

#endif // TESTHELPERS_H
