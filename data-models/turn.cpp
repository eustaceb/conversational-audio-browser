#include "turn.h"

Turn::Turn()
{

}

Turn::Turn(const double &startTime, const double &endTime, Speaker *speaker)
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

double Turn::getStartTime() const
{
    return startTime;
}

void Turn::setStartTime(const double &value)
{
    startTime = value;
}

double Turn::getEndTime() const
{
    return endTime;
}

void Turn::setEndTime(const double &value)
{
    endTime = value;
}
