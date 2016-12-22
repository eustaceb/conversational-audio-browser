#ifndef SPEAKER_H
#define SPEAKER_H

#include <QString>
#include "selectable.h"

class Speaker : public Selectable
{
public:
    Speaker();
    Speaker(const QString &id, const QString &name);

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    bool operator <(const Speaker &x) const;
    bool getSelected() const Q_DECL_OVERRIDE;
    void setSelected(bool value) Q_DECL_OVERRIDE;

private:
    bool selected;
    //TODO: Add more fields for
    // accent="" check="no" dialect="native" id="spk4" name="filler_c" scope="local" type="unknown"
    QString id;
    QString name;
};

#endif // SPEAKER_H
