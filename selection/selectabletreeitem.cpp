#include "selectabletreeitem.h"
SelectableTreeItem::SelectableTreeItem(Selectable *dataModel, SelectableTreeItem *parent)
    : dataModel(dataModel), parent(parent)
{
    payload = dataModel->composeTreePayload();
}

SelectableTreeItem::SelectableTreeItem(const QList<QVariant> &data, SelectableTreeItem *parent)
    : dataModel(0), parent(parent)
{
    payload = data;
}

SelectableTreeItem::~SelectableTreeItem()
{
    qDeleteAll(children);
}

void SelectableTreeItem::appendChild(SelectableTreeItem *item)
{
    children.append(item);
}

SelectableTreeItem *SelectableTreeItem::child(int index)
{
    return children.value(index);
}

int SelectableTreeItem::childCount() const
{
    return children.length();
}

int SelectableTreeItem::row() const
{
    if (parent)
        return parent->getChildren().indexOf(const_cast<SelectableTreeItem*>(this));
    return 0;
}

SelectableTreeItem *SelectableTreeItem::getParent()
{
    return parent;
}

int SelectableTreeItem::columnCount() const
{
    return payload.length();
}

QVariant SelectableTreeItem::data(int column) const
{
    return payload.value(column);
}

QList<SelectableTreeItem *> SelectableTreeItem::getChildren() const
{
    return children;
}
