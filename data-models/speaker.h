#ifndef SPEAKER_H
#define SPEAKER_H

#include <QString>

class Speaker
{
public:
    Speaker();
    Speaker(const QString &id, const QString &name);

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    bool operator <(const Speaker &x) const;
private:
    //TODO: Add more fields for
    // accent="" check="no" dialect="native" id="spk4" name="filler_c" scope="local" type="unknown"
    QString id;
    QString name;
};

#endif // SPEAKER_H
