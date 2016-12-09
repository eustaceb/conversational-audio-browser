#include "section.h"

#include <QDebug>
Section::Section()
{

}

void Section::addTurn(const Turn &turn)
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

Topic Section::getTopic() const
{
    return topic;
}

void Section::setTopic(const Topic &value)
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
/*
SectionGraphicsItem Section::getRegularGraphic() const
{
    return regularGraphic;
}

void Section::setRegularGraphic(const SectionGraphicsItem &value)
{
    regularGraphic = value;
}
*/
