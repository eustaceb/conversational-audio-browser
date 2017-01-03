#ifndef SPEAKER_H
#define SPEAKER_H

#include <QString>

class Turn;

#include "selection/selectable.h"

class Speaker : public Selectable
{
public:
    Speaker();
    Speaker(const QString &id, const QString &name);
    virtual ~Speaker();

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QList<Turn *> getTurns() const;
    void addTurn(Turn *t);

    bool operator <(const Speaker &x) const;

    // Selection tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;

private:
    //TODO: Add more fields for
    // accent="" check="no" dialect="native" id="spk4" name="filler_c" scope="local" type="unknown"
    QString id;
    QString name;

    QList <Turn*> turns;
};

#endif // SPEAKER_H
