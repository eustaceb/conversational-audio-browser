#include "topic.h"

Topic::Topic()
{

}

Topic::Topic(const QString &id, const QString &desc)
{
    this->id = id;
    this->desc = desc;
}

Topic::~Topic()
{
    // qDeleteAll(sections);
}

QString Topic::getId() const
{
    return id;
}

void Topic::setId(const QString &value)
{
    id = value;
}

void Topic::addSection(Section *s)
{
    sections.append(s);
}

QList<Section *> Topic::getSections() const
{
    return sections;
}


QList<QVariant> Topic::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append(id + " - " + desc);
    payload.append("topic");
    payload.append(QString::number(sections.length()) +" section(s)");
    return payload;
}

QString Topic::getDesc() const
{
    return desc;
}

void Topic::setDesc(const QString &value)
{
    desc = value;
}
