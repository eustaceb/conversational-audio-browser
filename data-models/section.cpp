#include "section.h"

#include <QDebug>

int Section::idCounter = 0;

Section::Section()
{
    id = idCounter;
    idCounter++;
}

Section::~Section()
{
    qDeleteAll(turns);
}

void Section::addTurn(Turn *turn)
{
    turns.append(turn);
}

double Section::getStartTime() const
{
    return startTime;
}

void Section::setStartTime(const double &value)
{
    startTime = value;

}

double Section::getEndTime() const
{
    return endTime;
}

void Section::setEndTime(const double &value)
{
    endTime = value;
}

Topic* Section::getTopic() const
{
    return topic;
}

void Section::setTopic(Topic *value)
{
    topic = value;
}

QList<Turn*> Section::getTurns() const
{
    return turns;
}

void Section::setTurns(const QList<Turn *> &value)
{
    turns = value;
}

QList<QVariant> Section::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append(QString::number(id) + " - " + topic->getDesc());
    payload.append("section");
    payload.append("From " + QString::number(startTime) + " to " + QString::number(endTime));
    return payload;
}

int Section::getId() const
{
    return id;
}
