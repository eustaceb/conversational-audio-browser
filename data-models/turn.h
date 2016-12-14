#ifndef TURN_H
#define TURN_H

#include <QString>
#include <QList>
#include "speaker.h"

class Turn
{
public:
    Turn();
    Turn(const double &startTime, const double &endTime, Speaker *speaker);

    void setSpeaker(Speaker *speaker);
    Speaker *getSpeaker() const;

    double getStartTime() const;
    void setStartTime(const double &value);

    double getEndTime() const;
    void setEndTime(const double &value);


private:
    double startTime;
    double endTime;

    Speaker *speaker;
};

#endif // TURN_H
