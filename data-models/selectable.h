#ifndef SELECTABLE_H
#define SELECTABLE_H

#include <QVariant>
#include <QList>


class Selectable
{
public:
    Selectable();
    bool isSelected() const;
    void setSelected(bool value);

    // Used by SelectionTreeItem
    virtual QList<QVariant> composeTreePayload() const = 0;

protected:
    bool selected;
};

#endif // SELECTABLE_H
