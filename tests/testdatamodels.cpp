#include "testdatamodels.h"

#include <data-models/filterable.h>
#include <data-models/selectable.h>
#include <data-models/transcription.h>
#include <data-models/speaker.h>
#include <data-models/turn.h>
#include <data-models/topic.h>
#include <data-models/section.h>

void TestDataModels::testTranscription()
{
    Transcription *trs = new Transcription("/tst/file1.trs");
    // Check whether fields are set correctly
    QCOMPARE(trs->getFilepath(), QString("/tst/file1.trs"));
    QCOMPARE(trs->getFilename(), QString("file1.trs"));
    QCOMPARE(trs->getTitle(), QString("file1"));

    // Check whether the lists were initialized correctly
    QCOMPARE(trs->getSpeakers().size(), 0);
    QCOMPARE(trs->getTopics().size(), 0);
    QCOMPARE(trs->getSectionList().size(), 0);
    QCOMPARE(trs->getTurnList().size(), 0);

    // See if all entities can be added correctly
    Speaker *s = new Speaker();
    trs->addSpeaker(s);
    QCOMPARE(trs->getSpeakers().size(), 1);
    QCOMPARE(trs->getSpeakers().at(0), s);


    Topic *t = new Topic();
    trs->addTopic(t);
    QCOMPARE(trs->getTopics().size(), 1);
    QCOMPARE(trs->getTopics().at(0), t);

    Section *sec = new Section();
    sec->setTopic(t);
    t->addSection(sec);
    QCOMPARE(trs->getSectionList().size(), 1);
    QCOMPARE(sec->getTopic(), t);
    QCOMPARE(trs->getTopics().at(0)->getSections().size(), 1);

    Turn *trn = new Turn(0, 0, s);
    s->addTurn(trn);
    sec->addTurn(trn);
    QCOMPARE(trs->getTurnList().size(), 1);
    QCOMPARE(trs->getTurnList().at(0), trn);
    QCOMPARE(trs->getSectionList().at(0)->getTurns().size(), 1);
    QCOMPARE(trs->getSpeakers().at(0)->getTurns().size(), 1);
    QCOMPARE(trs->getTopics().at(0)->getSections().at(0)->getTurns().size(), 1);

    // Check if tree payload is correct
    QList<QVariant> expected;
    expected.append("file1");
    expected.append("file1.trs");
    expected.append("transcription");
    expected.append("1 topics, 1 speakers");
    QCOMPARE(trs->composeTreePayload(), expected);

    delete trs;
}

void TestDataModels::testTopic()
{
    Topic *t = new Topic("to1", "Desc");
    // Field check
    QCOMPARE(t->getDesc(), QString("Desc"));
    QCOMPARE(t->getId(), QString("to1"));
    // See if section list is initialized
    QCOMPARE(t->getSections().size(), 0);
    // See if fields can be changed
    t->setDesc("Changed");
    QCOMPARE(t->getDesc(), QString("Changed"));
    t->setId("c1");
    QCOMPARE(t->getId(), QString("c1"));

    Section *s = new Section();
    s->setTopic(t);
    t->addSection(s);
    QCOMPARE(t->getSections().size(), 1);
    QCOMPARE(t->getSections().at(0), s);
    // Check if the tree payload is correct
    QList<QVariant> expected;
    expected.append("c1");
    expected.append("Changed");
    expected.append("topic");
    expected.append("1 section");
    QCOMPARE(t->composeTreePayload(), expected);

    delete t;
}

void TestDataModels::testSection()
{
    Section *s = new Section();
    // Field check
    s->setStartTime(1.25);
    QCOMPARE(s->getStartTime(), 1.25);
    s->setEndTime(5.75);
    QCOMPARE(s->getEndTime(), 5.75);
    QCOMPARE(s->getEndTime() - s->getStartTime(), 4.5);
    // See if turn list is initialized
    QCOMPARE(s->getTurns().size(), 0);
    // See if all entities are added correctly
    Topic *t = new Topic("to1", "test description");
    t->addSection(s);
    s->setTopic(t);
    QCOMPARE(s->getTopic(), t);

    Turn *trn = new Turn(0, 0, 0);
    Turn *trn2 = new Turn(0, 0, 0);
    s->addTurn(trn);
    QCOMPARE(s->getTurns().size(), 1);
    s->addTurn(trn2);
    QCOMPARE(s->getTurns().size(), 2);
    QCOMPARE(s->getTurns().at(0), trn);
    QCOMPARE(s->getTurns().at(1), trn2);
    // Check if the tree payload is correct
    QList<QVariant> expected;
    expected.append("sct" + QString::number(s->getId()));
    expected.append("test description");
    expected.append("section");
    expected.append("1.25 to 5.75");
    QCOMPARE(s->composeTreePayload(), expected);

    // Topic will delete all sections that it owns
    delete t;
}

void TestDataModels::testSpeaker()
{
    Speaker *s = new Speaker("tid", "test");
    // Field check
    QCOMPARE(s->getId(), QString("tid"));
    QCOMPARE(s->getName(), QString("test"));
    s->setId("oid");
    QCOMPARE(s->getId(), QString("oid"));
    s->setName("t2");
    QCOMPARE(s->getName(), QString("t2"));

    // List initialization check
    QCOMPARE(s->getTurns().size(), 0);

    // Entity check
    Turn *trn = new Turn(0, 0, 0);
    s->addTurn(trn);
    QCOMPARE(s->getTurns().size(), 1);
    Turn *trn2 = new Turn(0, 0, 0);
    s->addTurn(trn2);
    QCOMPARE(s->getTurns().size(), 2);
    QCOMPARE(s->getTurns().at(0), trn);
    QCOMPARE(s->getTurns().at(1), trn2);

    // Check tree payload
    QList<QVariant> expected;
    expected.append(QString("oid"));
    expected.append(QString("t2"));
    expected.append("speaker");
    expected.append(QString("2 turns"));

    delete s;
    delete trn;
    delete trn2;
}

void TestDataModels::testTurn()
{
    Speaker *s = new Speaker();
    s->setName("Me");
    Turn *trn = new Turn(1.23, 3.43, s);
    Turn *trn2 = new Turn(10000.27, 11000.87, s);
    // Check fields
    QCOMPARE(trn->getSpeaker(), s);
    QCOMPARE(trn->getStartTime(), 1.23);
    QCOMPARE(trn->getEndTime(), 3.43);
    QCOMPARE(trn2->getSpeaker(), s);
    QCOMPARE(trn2->getStartTime(), 10000.27);
    QCOMPARE(trn2->getEndTime(), 11000.87);
    QCOMPARE(trn->getDuration(), 2.2);
    QCOMPARE(trn2->getDuration(), 1000.6);

    // Check tree payload
    QList<QVariant> expected;
    expected.append("trn" + QString::number(trn->getId()));
    expected.append("Me");
    expected.append("turn");
    expected.append(QString("1.23 to 3.43"));
    QCOMPARE(trn->composeTreePayload(), expected);
    expected[0] = "trn" + QString::number(trn2->getId());
    expected[1] = "Me";
    expected[3] = QString("10000.27 to 11000.87");
    QCOMPARE(trn2->composeTreePayload(), expected);

    delete trn;
    delete trn2;
    delete s;
}
