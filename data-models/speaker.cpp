#include "speaker.h"

Speaker::Speaker()
{

}

Speaker::Speaker(const QString &id, const QString &name)
{
    this->id = id;
    this->name = name;
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
