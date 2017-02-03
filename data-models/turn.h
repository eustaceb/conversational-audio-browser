#ifndef TURN_H
#define TURN_H

#include <QVariant>
#include <QList>

#include "selectable.h"

class Speaker;

class Turn : public Selectable
{
public:
    Turn();
    Turn(const double &startTime, const double &endTime, Speaker *speaker);
    virtual ~Turn();

    void setSpeaker(Speaker *speaker);
    Speaker *getSpeaker() const;

    double getStartTime() const;
    void setStartTime(const double &value);

    double getEndTime() const;
    void setEndTime(const double &value);

    double getDuration() const;

    // Selection tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;

    int getId() const;

private:
    static int idCounter;
    int id;

    double startTime;
    double endTime;
    // Filter
    Speaker *speaker;
};

#endif // TURN_H
