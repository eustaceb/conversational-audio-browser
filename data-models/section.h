#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QList>

#include "selectable.h"

class Topic;
class Turn;

class Section : public Selectable
{
public:
    Section();
    virtual ~Section();

    int getId() const;

    void addTurn(Turn *turn);

    qreal getStartTime() const;
    void setStartTime(const qreal &value);

    qreal getEndTime() const;
    void setEndTime(const qreal &value);

    Topic *getTopic() const;
    void setTopic(Topic *value);

    QList<Turn*> getTurns() const;

    // Selection tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;

private:
    // <Section endTime="18.025" startTime="0.0" topic="to2" type="report">
    static int idCounter;
    int id;

    qreal startTime, endTime;
    Topic *topic;
    QList <Turn*> turns;
};

#endif // SECTION_H
