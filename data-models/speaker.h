#ifndef SPEAKER_H
#define SPEAKER_H

#include "filterable.h"
#include <QString>
#include <QList>
#include <QColor>

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

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    QString id;
    QString name;
    QColor color;

    QList <Turn*> turns;
};

#endif // SPEAKER_H
