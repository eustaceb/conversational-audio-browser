#ifndef FILTERTREEITEM_H
#define FILTERTREEITEM_H

#include "data-models/filterable.h"

class FilterTreeItem
{
public:
    FilterTreeItem(Filterable *dataModel, FilterTreeItem *parent = 0);
    FilterTreeItem(const QList<QVariant> &data, FilterTreeItem *parent = 0);
    virtual ~FilterTreeItem();

    void appendChild(FilterTreeItem *item);
    FilterTreeItem *child(int index);
    int childCount() const;
    int row() const;
    FilterTreeItem *getParent();

    int columnCount() const;
    QVariant data(int column) const;

    bool isFiltered() const;
    void setFiltered(bool value);

    QList<FilterTreeItem *> getChildren() const;

private:
    void propagateParentFiltering(bool value);
    void propagateChildrenFiltering(bool value);

    QList<QVariant> payload;
    Filterable *dataModel; // the datamodel that the tree item is bound to
    FilterTreeItem *parent;
    QList<FilterTreeItem*> children;
};

#endif // FILTERTREEITEM_H
