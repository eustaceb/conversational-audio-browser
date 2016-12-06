#ifndef TURN_H
#define TURN_H

#include <QString>
#include <QList>
#include <speaker.h>

class Turn
{
public:
    Turn();
    Turn(const QString &startTime, const QString &endTime, const QString &speaker);

    void addSpeaker(const Speaker &speaker);

    QString getStartTime() const;
    void setStartTime(const QString &value);

    QString getEndTime() const;
    void setEndTime(const QString &value);

    QList<Speaker> getSpeakers() const;
    void setSpeakers(const QList<Speaker> &value);

    QString getSpeaker() const;
    void setSpeaker(const QString &value);

private:
    QString speaker;
    QString startTime;
    QString endTime;
    QList <Speaker> speakers;
};

#endif // TURN_H
