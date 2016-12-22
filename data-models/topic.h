#ifndef TOPIC_H
#define TOPIC_H

#include <QString>
#include "selectable.h"

class Topic : public Selectable
{
public:
    Topic();
    Topic(const QString &id, const QString &desc);

    QString getDesc() const;
    void setDesc(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    bool getSelected() const Q_DECL_OVERRIDE;
    void setSelected(bool value) Q_DECL_OVERRIDE;

protected:

private:
    bool selected;
    // TODO: Should have a list of section objects
    QString desc;
    QString id;
};
#endif // TOPIC_H
