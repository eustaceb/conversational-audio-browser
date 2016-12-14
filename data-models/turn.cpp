#include "turn.h"

Turn::Turn()
{

}

Turn::Turn(const QString &startTime, const QString &endTime, Speaker *speaker)
{
    this->startTime = startTime;
    this->endTime = endTime;
    this->speaker = speaker;
}

void Turn::setSpeaker(Speaker *speaker)
{
    this->speaker = speaker;
}

Speaker *Turn::getSpeaker() const
{
    return speaker;
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
