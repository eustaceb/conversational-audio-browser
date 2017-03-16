#include "section.h"
#include "topic.h"
#include "turn.h"

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

QList<QVariant> Section::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append("sct" + QString::number(id));
    payload.append(topic->getDesc());
    payload.append("section");
    payload.append(QString::number(startTime) + " to " + QString::number(endTime));
    return payload;
}

int Section::getId() const
{
    return id;
}
