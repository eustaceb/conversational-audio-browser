#ifndef SPEAKER_H
#define SPEAKER_H

#include "filterable.h"
#include <QString>
#include <QList>

class Turn;

class Speaker : public Filterable
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

    // Filter tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;

    double getTotalTurnLength() const;

private:
    //TODO: Add more fields for
    // accent="" check="no" dialect="native" id="spk4" name="filler_c" scope="local" type="unknown"
    QString id;
    QString name;

    QList <Turn*> turns;
    double totalTurnLength;
};

#endif // SPEAKER_H
