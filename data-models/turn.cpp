#include "turn.h"
#include "speaker.h"

int Turn::idCounter = 0;

Turn::Turn(const qreal &startTime, const qreal &endTime, Speaker *speaker)
    : id(++idCounter)
{
    this->startTime = startTime;
    this->endTime = endTime;
    this->speaker = speaker;
}

Turn::~Turn()
{

}

Speaker *Turn::getSpeaker() const
{
    return speaker;
}

qreal Turn::getStartTime() const
{
    return startTime;
}

qreal Turn::getEndTime() const
{
    return endTime;
}

qreal Turn::getDuration() const
{
    return endTime - startTime;
}

QList<QVariant> Turn::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append("trn" + QString::number(id));
    payload.append(speaker->getName());
    payload.append("turn");
    payload.append(QString::number(startTime, 'g', 8) + " to " + QString::number(endTime, 'g', 8));
    return payload;
}

int Turn::getId() const
{
    return id;
}
