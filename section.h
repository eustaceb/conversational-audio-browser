#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QList>
#include <turn.h>

class Section
{
public:
    Section();
    Section(const QString &startTime, const QString &endTime, const QString &topic);

    void addTurn(const Turn &turn);

    QString getStartTime() const;
    void setStartTime(const QString &value);

    QString getEndTime() const;
    void setEndTime(const QString &value);

    QString getTopic() const;
    void setTopic(const QString &value);

    QList<Turn> getTurns() const;
    void setTurns(const QList<Turn> &value);

private:
    // <Section endTime="18.025" startTime="0.0" topic="to2" type="report">
    QString startTime;
    QString endTime;
    QString topic; // TODO: Refer to Topic class
    QList <Turn> turns;
};

#endif // SECTION_H
