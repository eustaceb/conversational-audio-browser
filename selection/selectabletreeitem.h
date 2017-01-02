#ifndef SELECTABLETREEITEM_H
#define SELECTABLETREEITEM_H
#include <QString>
#include <QList>
#include <QVariant>
#include "selectable.h"

class SelectableTreeItem {
public:
    SelectableTreeItem(Selectable *dataModel, SelectableTreeItem *parent = 0);
    SelectableTreeItem(const QList<QVariant> &data, SelectableTreeItem *parent = 0);
    virtual ~SelectableTreeItem();

    void appendChild(SelectableTreeItem *item);
    SelectableTreeItem *child(int index);
    int childCount() const;
    int row() const;
    SelectableTreeItem *getParent();

    int columnCount() const;
    QVariant data(int column) const;

    QList<SelectableTreeItem *> getChildren() const;

private:
    QList<QVariant> payload;
    Selectable *dataModel; // the datamodel that the tree item is bound to
    SelectableTreeItem *parent;
    QList<SelectableTreeItem*> children;
};
#endif // SELECTABLETREEITEM_H
