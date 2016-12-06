#ifndef TOPIC_H
#define TOPIC_H

#include <QString>

class Topic
{
public:
    Topic();
    Topic(const QString &id, const QString &desc);

    QString getDesc() const;
    void setDesc(const QString &value);

    QString getId() const;
    void setId(const QString &value);

protected:

private:
    // TODO: Should have a list of section objects
    QString desc;
    QString id;
};
#endif // TOPIC_H
