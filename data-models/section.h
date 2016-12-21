#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QList>
#include "turn.h"
#include "topic.h"
//#include "drawables/regular/sectiongraphicsitem.h"

class Section
{
public:
    Section();
    ~Section();

    void addTurn(Turn *turn);

    double getStartTime() const;
    void setStartTime(const double &value);

    double getEndTime() const;
    void setEndTime(const double &value);

    Topic* getTopic() const;
    void setTopic(Topic *value);

    QList<Turn*> getTurns() const;
    void setTurns(const QList<Turn*> &value);
/*
    SectionGraphicsItem getRegularGraphic() const;
    void setRegularGraphic(const SectionGraphicsItem &value);
*/
private:
    // <Section endTime="18.025" startTime="0.0" topic="to2" type="report">
    double startTime, endTime;
    Topic *topic;
    QList <Turn*> turns;
};

#endif // SECTION_H
