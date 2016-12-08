#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QList>
#include "turn.h"
//#include "drawables/regular/sectiongraphicsitem.h"

class Section
{
public:
    Section();
    Section(const double &startTime, const double &endTime, const double &topic);

    void addTurn(const Turn &turn);

    double getStartTime() const;
    void setStartTime(const double &value);

    double getEndTime() const;
    void setEndTime(const double &value);

    QString getTopic() const;
    void setTopic(const QString &value);

    QList<Turn> getTurns() const;
    void setTurns(const QList<Turn> &value);
/*
    SectionGraphicsItem getRegularGraphic() const;
    void setRegularGraphic(const SectionGraphicsItem &value);
*/
private:
    // <Section endTime="18.025" startTime="0.0" topic="to2" type="report">
    double startTime, endTime;
    QString topic; // TODO: Refer to Topic class
    QList <Turn> turns;
    //SectionGraphicsItem regularGraphic; // might be useless
};

#endif // SECTION_H
