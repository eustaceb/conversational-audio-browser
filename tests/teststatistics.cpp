#include "teststatistics.h"

#include "data-models/filterable.h"
#include "data-models/selectable.h"
#include "data-models/transcription.h"
#include "data-models/recording.h"
#include "data-models/speaker.h"
#include "data-models/turn.h"
#include "data-models/topic.h"
#include "data-models/section.h"

#include "helpers.h"
#include "statistics.h"

#include <QBuffer>

// The default QCOMPARE epsilon is too low
bool TestStatistics::areRealsEqual(qreal actual, qreal expected, qreal epsilon)
{
    return (actual - epsilon <= expected && actual + epsilon >=expected);
}

void TestStatistics::initTestCase()
{
    // Create a mock transcription from xml
    QString header = QString("<?xml version=\"1.0\" encoding=\"utf-8\"?><Trans>");
    QString topics = QString("<Topic desc=\"paper\" id=\"to1\" /><Topic desc=\"rock\" id=\"to2\" />");
    QString speakers = QString("<Speaker id=\"spk1\" name=\"laughter\" /><Speaker id=\"spk2\" name=\"sneeze\" />");
    QString sectionsWTurns = QString("<Section endTime=\"12.65\" startTime=\"0.0\" topic=\"to1\">");
    sectionsWTurns += QString("<Turn endTime=\"1.5\" speaker=\"spk1\" startTime=\"0.0\"></Turn>");
    sectionsWTurns += QString("<Turn endTime=\"6.6\" speaker=\"spk2\" startTime=\"2.1\"></Turn>");
    sectionsWTurns += QString("<Turn endTime=\"11.95\" speaker=\"spk1\" startTime=\"7.15\"></Turn>");
    sectionsWTurns += QString("</Section>");
    sectionsWTurns += QString("<Section endTime=\"21\" startTime=\"12.65\" topic=\"to2\">");
    sectionsWTurns += QString("<Turn endTime=\"12.95\" speaker=\"spk1\" startTime=\"12.65\"></Turn>");
    sectionsWTurns += QString("<Turn endTime=\"14.7\" speaker=\"spk2\" startTime=\"13\"></Turn>");
    sectionsWTurns += QString("<Turn endTime=\"21\" speaker=\"spk1\" startTime=\"20\"></Turn>");
    sectionsWTurns += QString("</Section></Trans>");
    QString transcriptionStr = header + topics + speakers + sectionsWTurns;

    // Two speakers - laughter and sneeze + the default "none"
    // Two topics - paper and rock
    // Two sections - one for paper, one for rock
    // Turn lengths:
    // -----------------------------------------+
    // laughter| 1.5      4.8  |0.3         1   |
    // sneeze  |       4.5     |    1.7         |
    //         |paperpaperpaper|rockrockrockrock|
    // -----------------------------------------+

    // Turns for the whole transcription: 1.5,4.5,4.8,0.3,1.7,1
    // Turns for laughter: 1.5,4.8,0.3,1
    // Turns for sneeze: 4.5,1.7
    // Turns for paper or sec1: 1.5,4.8,4.5
    // Turns for rock or sec2: 0.3,1.7,1

    // Turn into an QIODevice by using the QBuffer
    QByteArray *bytes = new QByteArray(transcriptionStr.toUtf8());
    QBuffer *device = new QBuffer(bytes);
    device->setObjectName("/some/file.trs");

    trs = Helpers::parseTranscript(device);
    delete bytes;
    delete device;
}

void TestStatistics::cleanupTestCase()
{
    delete trs;
}

void TestStatistics::testMedian()
{
    qreal m = Statistics::median(QList<qreal>({1, 2, 5.5, 4, 3.2}));
    QCOMPARE(m, 3.2);
    m = Statistics::median(QList<qreal>({1, 2, 5.5, 4, 3.2, 6}));
    QCOMPARE(m, 3.6);
}

void TestStatistics::testTurnCount()
{
    // Whole Transcription
    QCOMPARE(Statistics::turnCount(trs), 6);

    // Speaker: None
    QCOMPARE(Statistics::turnCount(trs->getSpeakers().at(0)), 0);
    // Speaker: Laughter
    QCOMPARE(Statistics::turnCount(trs->getSpeakers().at(1)), 4);
    // Speaker: Sneeze
    QCOMPARE(Statistics::turnCount(trs->getSpeakers().at(2)), 2);

    // Topic: Paper
    QCOMPARE(Statistics::turnCount(trs->getTopics().at(0)), 3);
    // Topic: Rock
    QCOMPARE(Statistics::turnCount(trs->getTopics().at(1)), 3);

    // Section 1 - paper
    QCOMPARE(Statistics::turnCount(trs->getTopics().at(0)->getSections().at(0)), 3);
    // Section 2 - rock
    QCOMPARE(Statistics::turnCount(trs->getTopics().at(1)->getSections().at(0)), 3);
}

void TestStatistics::testTurnLength()
{
    // Whole Transcription
    QCOMPARE(Statistics::turnLength(trs), 1.5+4.5+4.8+0.3+1.7+1);

    // Speaker: None
    QCOMPARE(Statistics::turnLength(trs->getSpeakers().at(0)), 0.0);
    // Speaker: Laughter
    QCOMPARE(Statistics::turnLength(trs->getSpeakers().at(1)), 1.5+4.8+0.3+1);
    // Speaker: Sneeze
    QCOMPARE(Statistics::turnLength(trs->getSpeakers().at(2)), 4.5+1.7);

    // Topic: Paper
    QCOMPARE(Statistics::turnLength(trs->getTopics().at(0)), 1.5+4.8+4.5);
    // Topic: Rock
    QCOMPARE(Statistics::turnLength(trs->getTopics().at(1)), 0.3+1.7+1);

    // Section 1 - paper
    QCOMPARE(Statistics::turnLength(trs->getTopics().at(0)->getSections().at(0)), 1.5+4.5+4.8);
    // Section 2 - rock
    QCOMPARE(Statistics::turnLength(trs->getTopics().at(1)->getSections().at(0)), 0.3+1.7+1);
}

void TestStatistics::testMedianTurnLength()
{
    // Whole Transcription
    QCOMPARE(Statistics::medianTurnLength(trs), 1.6);

    // Speaker: None
    QVERIFY(std::isnan(Statistics::medianTurnLength(trs->getSpeakers().at(0))));
    // Speaker: Laughter
    QCOMPARE(Statistics::medianTurnLength(trs->getSpeakers().at(1)), 1.25);
    // Speaker: Sneeze
    QCOMPARE(Statistics::medianTurnLength(trs->getSpeakers().at(2)), 3.1);

    // Topic: Paper
    QCOMPARE(Statistics::medianTurnLength(trs->getTopics().at(0)), 4.5);
    // Topic: Rock
    QCOMPARE(Statistics::medianTurnLength(trs->getTopics().at(1)), 1.0);

    // Section 1 - paper
    QCOMPARE(Statistics::medianTurnLength(trs->getTopics().at(0)->getSections().at(0)), 4.5);
    // Section 2 - rock
    QCOMPARE(Statistics::medianTurnLength(trs->getTopics().at(1)->getSections().at(0)), 1.0);
}

void TestStatistics::testTurnLengthVariance()
{
    // Whole Transcription
    QVERIFY(areRealsEqual(Statistics::turnLengthVariance(trs), 2.9633333333333));

    // Speaker: None
    QVERIFY(std::isnan(Statistics::turnLengthVariance(trs->getSpeakers().at(0))));
    // Speaker: Laughter
    QCOMPARE(Statistics::turnLengthVariance(trs->getSpeakers().at(1)), 2.985);
    // Speaker: Sneeze
    QCOMPARE(Statistics::turnLengthVariance(trs->getSpeakers().at(2)), 1.96);

    // Topic: Paper
    QCOMPARE(Statistics::turnLengthVariance(trs->getTopics().at(0)), 2.22);
    // Topic: Rock
    QVERIFY(areRealsEqual(Statistics::turnLengthVariance(trs->getTopics().at(1)), 0.32666666666667));

    // Section 1 - paper
    QCOMPARE(Statistics::turnLengthVariance(trs->getTopics().at(0)->getSections().at(0)), 2.22);
    // Section 2 - rock
    QVERIFY(areRealsEqual(Statistics::turnLengthVariance(trs->getTopics().at(1)->getSections().at(0)), 0.32666666666667));
}

void TestStatistics::testTurnLengthSkewness()
{
    // Whole Transcription
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs), 1.21991351184));

    // Speaker: None
    QVERIFY(std::isnan(Statistics::turnLengthSkewness(trs->getSpeakers().at(0))));
    // Speaker: Laughter
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getSpeakers().at(1)), 1.12865820634));
    // Speaker: Sneeze
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getSpeakers().at(2)), 0.0));

    // Topic: Paper
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getTopics().at(0)), -1.81212134908));
    // Topic: Rock
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getTopics().at(1)), 0.0));

    // Section 1 - paper
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getTopics().at(0)->getSections().at(0)), -1.81212134908));
    // Section 2 - rock
    QVERIFY(areRealsEqual(Statistics::turnLengthSkewness(trs->getTopics().at(1)->getSections().at(0)), 0.0));
}

void TestStatistics::testTurnLengthRange()
{
    // Whole Transcription
    QPair<qreal, qreal> pair = Statistics::turnLengthRange(trs);
    QCOMPARE(pair.first, 0.3);
    QCOMPARE(pair.second, 4.8);

    // Speaker: None
    pair = Statistics::turnLengthRange(trs->getSpeakers().at(0));
    QCOMPARE(pair.first, 0.0);
    QCOMPARE(pair.second, 0.0);
    // Speaker: Laughter
    pair = Statistics::turnLengthRange(trs->getSpeakers().at(1));
    QCOMPARE(pair.first, 0.3);
    QCOMPARE(pair.second, 4.8);
    // Speaker: Sneeze
    pair = Statistics::turnLengthRange(trs->getSpeakers().at(2));
    QCOMPARE(pair.first, 1.7);
    QCOMPARE(pair.second, 4.5);

    // Topic: Paper
    pair = Statistics::turnLengthRange(trs->getTopics().at(0));
    QCOMPARE(pair.first, 1.5);
    QCOMPARE(pair.second, 4.8);
    // Topic: Rock
    pair = Statistics::turnLengthRange(trs->getTopics().at(1));
    QCOMPARE(pair.first, 0.3);
    QCOMPARE(pair.second, 1.7);

    // Section 1 - paper
    pair = Statistics::turnLengthRange(trs->getTopics().at(0)->getSections().at(0));
    QCOMPARE(pair.first, 1.5);
    QCOMPARE(pair.second, 4.8);
    // Section 2 - rock
    pair = Statistics::turnLengthRange(trs->getTopics().at(1)->getSections().at(0));
    QCOMPARE(pair.first, 0.3);
    QCOMPARE(pair.second, 1.7);
}

