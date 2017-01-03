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

bool SelectableTreeItem::isSelected() const
{
    return dataModel->isSelected();
}

void SelectableTreeItem::setSelected(bool value)
{
    dataModel->setSelected(value);
}

void SelectableTreeItem::propagateSelected(bool value)
{
    propagateChildrenSelection(value);
    if (parent)
        parent->propagateParentSelection(value);
}

void SelectableTreeItem::propagateParentSelection(bool value)
{
    // If parent has a data model - determine its status
    if (dataModel) {
        // If propagating a true value - set it to true since at least one child will be checked
        if (value) {
            dataModel->setSelected(value);
        // Otherwise - go through all children to see if at least one child is checked
        } else {
            dataModel->setSelected(false);
            foreach(SelectableTreeItem *c, children) {
                if (c->isSelected()) {
                    dataModel->setSelected(true);
                    break;
                }
            }
        }
    }
    // Propagate up
    if (parent)
        parent->propagateParentSelection(value);
}

void SelectableTreeItem::propagateChildrenSelection(bool value)
{
    dataModel->setSelected(value);
    for (int i = 0; i < children.length(); i++) {
        children.at(i)->propagateChildrenSelection(value);
    }
}

QList<SelectableTreeItem *> SelectableTreeItem::getChildren() const
{
    return children;
}
