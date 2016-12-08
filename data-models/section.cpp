#include "section.h"

#include <QDebug>
Section::Section()
{

}

Section::Section(const double &startTime, const double &endTime, const double &topic)
{
    this->startTime = startTime;
    this->endTime = endTime;
    this->topic = topic;
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
