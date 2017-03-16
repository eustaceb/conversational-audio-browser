#ifndef TURN_H
#define TURN_H

#include <QVariant>
#include <QList>

#include "selectable.h"

class Speaker;

class Turn : public Selectable
{
public:
    Turn(const double &startTime, const double &endTime, Speaker *speaker);
    virtual ~Turn();

    int getId() const;
    Speaker *getSpeaker() const;
    double getStartTime() const;
    double getEndTime() const;
    double getDuration() const;

    // Payload for Selection tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;


private:
    static int idCounter;
    int id;

    double startTime;
    double endTime;
    // Ownership, 1 speaker : m turns
    Speaker *speaker;
};

#endif // TURN_H
