#ifndef FILTERABLE_H
#define FILTERABLE_H

#include <QList>
#include <QVariant>

class Filterable
{
public:
    Filterable();

    bool isFiltered() const;
    void setFiltered(bool value);

    // Used by FilterTreeItem
    virtual QList<QVariant> composeTreePayload() const = 0;

protected:
    bool filtered;
};

#endif // FILTERABLE_H
