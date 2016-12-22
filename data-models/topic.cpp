#include "topic.h"

Topic::Topic()
{

}

Topic::Topic(const QString &id, const QString &desc)
{
    this->id = id;
    this->desc = desc;
}

QString Topic::getId() const
{
    return id;
}

void Topic::setId(const QString &value)
{
    id = value;
}

bool Topic::getSelected() const
{
    return selected;
}

void Topic::setSelected(bool value)
{
    selected = value;
}

QString Topic::getDesc() const
{
    return desc;
}

void Topic::setDesc(const QString &value)
{
    desc = value;
}
