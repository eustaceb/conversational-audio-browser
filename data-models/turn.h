#ifndef TURN_H
#define TURN_H

#include <QString>
#include <QList>
#include "speaker.h"

class Turn : public Selectable
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

    bool getSelected() const Q_DECL_OVERRIDE;
    void setSelected(bool value) Q_DECL_OVERRIDE;

private:
    bool selected;

    double startTime;
    double endTime;

    Speaker *speaker;
};

#endif // TURN_H
