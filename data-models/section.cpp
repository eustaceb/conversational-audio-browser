#include "section.h"

#include <QDebug>
Section::Section()
{

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

bool Section::getSelected() const
{
    return selected;
}

void Section::setSelected(bool value)
{
    selected = value;
    foreach (Turn *t, turns) {
        t->setSelected(value);
    }
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
