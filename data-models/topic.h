#ifndef TOPIC_H
#define TOPIC_H

#include "selectable.h"
#include <QString>
#include <QList>

class Section;

class Topic : public Selectable
{
public:
    Topic();
    Topic(const QString &id, const QString &desc);
    virtual ~Topic();

    QString getDesc() const;
    void setDesc(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    void addSection(Section *s);
    QList<Section *> getSections() const;

    // Selection tree
    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;

private:
    QString desc;
    QString id;
    QList<Section *> sections;
};
#endif // TOPIC_H
