#include "turn.h"

Turn::Turn()
{

}

Turn::Turn(const QString &startTime, const QString &endTime, const QString &speaker)
{
    this->startTime = startTime;
    this->endTime = endTime;
}

void Turn::addSpeaker(const Speaker &speaker)
{
    this->speakers.append(speaker);
}

QString Turn::getStartTime() const
{
    return startTime;
}

void Turn::setStartTime(const QString &value)
{
    startTime = value;
}

QString Turn::getEndTime() const
{
    return endTime;
}

void Turn::setEndTime(const QString &value)
{
    endTime = value;
}

QList<Speaker> Turn::getSpeakers() const
{
    return speakers;
}

void Turn::setSpeakers(const QList<Speaker> &value)
{
    speakers = value;
}
