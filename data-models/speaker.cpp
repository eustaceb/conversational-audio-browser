#include "speaker.h"

Speaker::Speaker()
{

}

Speaker::Speaker(const QString &id, const QString &name)
{
    this->id = id;
    this->name = name;
}

Speaker::~Speaker()
{

}

QString Speaker::getId() const
{
    return id;
}

void Speaker::setId(const QString &value)
{
    id = value;
}

QString Speaker::getName() const
{
    return name;
}

void Speaker::setName(const QString &value)
{
    name = value;
}

bool Speaker::operator <(const Speaker& x) const
{
    return name < x.getName();
}

QList<QVariant> Speaker::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append(id);
    payload.append(name);
    payload.append("speaker");
    payload.append(turns.size() + "turn(s)");
    return payload;
}

QList<Turn *> Speaker::getTurns() const
{
    return turns;
}

void Speaker::addTurn(Turn *t)
{
    turns.append(t);
}
