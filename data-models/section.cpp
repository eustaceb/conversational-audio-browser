#include "section.h"


Section::Section()
{

}

Section::Section(const QString &startTime, const QString &endTime, const QString &topic)
{
    this->startTime = startTime;
    this->endTime = endTime;
    this->topic = topic;
}

void Section::addTurn(const Turn &turn)
{
    turns.append(turn);
}

QString Section::getStartTime() const
{
    return startTime;
}

void Section::setStartTime(const QString &value)
{
    startTime = value;
}

QString Section::getEndTime() const
{
    return endTime;
}

void Section::setEndTime(const QString &value)
{
    endTime = value;
}

QString Section::getTopic() const
{
    return topic;
}

void Section::setTopic(const QString &value)
{
    topic = value;
}

QList<Turn> Section::getTurns() const
{
    return turns;
}

void Section::setTurns(const QList<Turn> &value)
{
    turns = value;
}
