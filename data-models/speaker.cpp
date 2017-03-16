#include "speaker.h"
#include "turn.h"

#include "helpers.h"
#include "math.h"

Speaker::Speaker()
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
}

Speaker::Speaker(const QString &id, const QString &name)
{
    this->id = id;
    this->name = name;
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
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
    payload.append(QString::number(turns.size()) + (turns.size() == 1 ? " turn" : " turns"));
    return payload;
}

QColor Speaker::getColor() const
{
    return color;
}

void Speaker::setColor(const QColor &value)
{
    color = value;
}

QList<Turn *> Speaker::getTurns() const
{
    return turns;
}

void Speaker::addTurn(Turn *t)
{
    turns.append(t);
}
