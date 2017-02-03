#include "turn.h"
#include "speaker.h"

int Turn::idCounter = 0;

Turn::Turn()
    : id(++idCounter)
{
}

Turn::Turn(const double &startTime, const double &endTime, Speaker *speaker)
    : id(++idCounter)
{
    this->startTime = startTime;
    this->endTime = endTime;
    this->speaker = speaker;
}

Turn::~Turn()
{

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

double Turn::getDuration() const
{
    return endTime - startTime;
}

QList<QVariant> Turn::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append("trn" + QString::number(id));
    payload.append(speaker->getName());
    payload.append("turn");
    payload.append(QString::number(startTime) + " to " + QString::number(endTime));
    return payload;
}

int Turn::getId() const
{
    return id;
}

