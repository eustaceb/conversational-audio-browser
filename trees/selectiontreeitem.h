#ifndef SELECTIONTREEITEM_H
#define SELECTIONTREEITEM_H
#include <QString>
#include <QList>
#include <QVariant>

#include "data-models/selectable.h"

class SelectionTreeItem {
public:
    SelectionTreeItem(Selectable *dataModel, SelectionTreeItem *parent = 0);
    SelectionTreeItem(const QList<QVariant> &data, SelectionTreeItem *parent = 0);
    virtual ~SelectionTreeItem();

    void appendChild(SelectionTreeItem *item);
    SelectionTreeItem *child(int index);
    int childCount() const;
    int row() const;
    SelectionTreeItem *getParent();

    int columnCount() const;
    QVariant data(int column) const;

    bool isSelected() const;
    void setSelected(bool value);
    void propagateSelected(bool value);

    QList<SelectionTreeItem *> getChildren() const;

    Selectable *getDataModel() const;

private:
    void propagateParentSelection(bool value);
    void propagateChildrenSelection(bool value);

    QList<QVariant> payload;
    Selectable *dataModel; // the datamodel that the tree item is bound to
    SelectionTreeItem *parent;
    QList<SelectionTreeItem *> children;
};
#endif // SELECTIONTREEITEM_H
