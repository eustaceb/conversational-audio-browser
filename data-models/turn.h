#ifndef TURN_H
#define TURN_H

#include <QString>
#include <QList>
#include "speaker.h"

class Turn
{
public:
    Turn();
    Turn(const QString &startTime, const QString &endTime, Speaker *speaker);

    void setSpeaker(Speaker *speaker);
    Speaker *getSpeaker() const;

    QString getStartTime() const;
    void setStartTime(const QString &value);

    QString getEndTime() const;
    void setEndTime(const QString &value);


private:
    QString startTime;
    QString endTime;

    Speaker *speaker;
};

#endif // TURN_H
