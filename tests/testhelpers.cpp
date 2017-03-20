#include "testhelpers.h"

#include "data-models/filterable.h"
#include "data-models/selectable.h"
#include "data-models/transcription.h"
#include "data-models/speaker.h"
#include "data-models/turn.h"
#include "data-models/topic.h"
#include "data-models/section.h"

#include "helpers.h"
#include <QDebug>

void TestHelpers::testParseTranscription()
{
    Transcription *trs;
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
    sectionsWTurns += QString("</Section>");
    // Add one empty section
    sectionsWTurns += QString("<Section startTime=\"21.68\" endTime=\"31\" topic=\"to1\"></Section></Trans>");
    QString transcriptionStr = header + topics + speakers + sectionsWTurns;

    // Turn into an QIODevice by using the QBuffer
    QByteArray *bytes = new QByteArray(transcriptionStr.toUtf8());
    QBuffer *device = new QBuffer(bytes);
    device->setObjectName("/some/file.trs");

    trs = Helpers::parseTranscript(device);
    delete bytes;
    delete device;

    // Validate fields
    QCOMPARE(trs->getFilepath(), QString("/some/file.trs"));
    QCOMPARE(trs->getFilename(), QString("file.trs"));
    QCOMPARE(trs->getTitle(), QString("file"));

    //qInfo() << trs->getTopics().size() << trs->getSpeakers().size() << trs->getSectionList().size() << trs->getTurnList().size();
    // Validate lists
    QCOMPARE(trs->getSectionList().size(), 3);
    QCOMPARE(trs->getSpeakers().size(), 3);
    QCOMPARE(trs->getTopics().size(), 2);
    QCOMPARE(trs->getTurnList().size(), 6);
    // Compare actual contents
    Topic *paper = trs->getTopics().at(0);
    Topic *rock = trs->getTopics().at(1);
    QVERIFY(paper->getDesc() == QString("paper") && paper->getId() == QString("to1"));
    QVERIFY(rock->getDesc() == QString("rock") && rock->getId() == QString("to2"));
    QCOMPARE(paper->getSections().size(), 2);
    QCOMPARE(rock->getSections().size(), 1);
    // Speakers
    Speaker *laughter = trs->getSpeakers().at(1);
    Speaker *sneeze = trs->getSpeakers().at(2);
    QVERIFY(laughter->getName() == QString("laughter") && laughter->getId() == QString("spk1"));
    QVERIFY(sneeze->getName() == QString("sneeze") && sneeze->getId() == QString("spk2"));
    // Sections
    Section *first = paper->getSections().at(0);
    QCOMPARE(first, trs->getSectionList().at(0));
    QVERIFY(first->getStartTime() == 0 && first->getEndTime() == 12.65 && first->getTopic() == paper);
    QCOMPARE(first->getTurns().size(), 3);

    Section *empty = paper->getSections().at(1);
    QCOMPARE(empty, trs->getSectionList().at(1));
    QVERIFY(empty->getStartTime() == 21.68 && empty->getEndTime() == 31 && empty->getTopic() == paper);
    QCOMPARE(empty->getTurns().size(), 0);

    Section *second = rock->getSections().at(0);
    QCOMPARE(second, trs->getSectionList().at(2));
    QVERIFY(second->getStartTime() == 12.65 && second->getEndTime() == 21 && second->getTopic() == rock);
    QCOMPARE(second->getTurns().size(), 3);

    // Turns
    // First section
    Turn *t1 = first->getTurns().at(0);
    QCOMPARE(t1, trs->getTurnList().at(0));
    QVERIFY(t1->getStartTime() == 0 && t1->getEndTime() == 1.5);
    QCOMPARE(t1->getSpeaker(), laughter);
    QCOMPARE(t1->getDuration(), 1.5);

    Turn *t2 = first->getTurns().at(1);
    QCOMPARE(t2, trs->getTurnList().at(4)); // Speaker 2, therefore (4 + 1) - 1
    QVERIFY(t2->getStartTime() == 2.1 && t2->getEndTime() == 6.6);
    QCOMPARE(t2->getSpeaker(), sneeze);
    QCOMPARE(t2->getDuration(), 4.5);

    Turn *t3 = first->getTurns().at(2);
    QCOMPARE(t3, trs->getTurnList().at(1));
    QVERIFY(t3->getStartTime() == 7.15 && t3->getEndTime() == 11.95);
    QCOMPARE(t3->getSpeaker(), laughter);
    QCOMPARE(t3->getDuration(), 4.8);

    // Second section
    Turn *t4 = second->getTurns().at(0);
    QCOMPARE(t4, trs->getTurnList().at(2));
    QVERIFY(t4->getStartTime() == 12.65 && t4->getEndTime() == 12.95);
    QCOMPARE(t4->getSpeaker(), laughter);
    QCOMPARE(t4->getDuration(), 0.3);

    Turn *t5 = second->getTurns().at(1);
    QCOMPARE(t5, trs->getTurnList().at(5));
    QVERIFY(t5->getStartTime() == 13 && t5->getEndTime() == 14.7);
    QCOMPARE(t5->getSpeaker(), sneeze);
    QCOMPARE(t5->getDuration(), 1.7);

    Turn *t6 = second->getTurns().at(2);
    QCOMPARE(t6, trs->getTurnList().at(3));
    QVERIFY(t6->getStartTime() == 20 && t6->getEndTime() == 21);
    QCOMPARE(t6->getSpeaker(), laughter);
    //QCOMPARE(t6->getDuration(), 1);

    delete trs;
}
