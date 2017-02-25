#include "selectiontreeitem.h"

SelectionTreeItem::SelectionTreeItem(Selectable *dataModel, SelectionTreeItem *parent)
    : dataModel(dataModel), parent(parent)
{
    payload = dataModel->composeTreePayload();
}

SelectionTreeItem::SelectionTreeItem(const QList<QVariant> &data, SelectionTreeItem *parent)
    : dataModel(0), parent(parent)
{
    payload = data;
}

SelectionTreeItem::~SelectionTreeItem()
{
    qDeleteAll(children);
}

void SelectionTreeItem::appendChild(SelectionTreeItem *item)
{
    children.append(item);
}

SelectionTreeItem *SelectionTreeItem::child(int index)
{
    return children.value(index);
}

int SelectionTreeItem::childCount() const
{
    return children.length();
}

int SelectionTreeItem::row() const
{
    if (parent)
        return parent->getChildren().indexOf(const_cast<SelectionTreeItem*>(this));
    return 0;
}

SelectionTreeItem *SelectionTreeItem::getParent()
{
    return parent;
}

int SelectionTreeItem::columnCount() const
{
    return payload.length();
}

QVariant SelectionTreeItem::data(int column) const
{
    return payload.value(column);
}

bool SelectionTreeItem::isSelected() const
{
    return dataModel->isSelected();
}

void SelectionTreeItem::setSelected(bool value)
{
    dataModel->setSelected(value);
}

void SelectionTreeItem::propagateSelected(bool value)
{
    propagateChildrenSelection(value);
    if (parent)
        parent->propagateParentSelection(value);
}

void SelectionTreeItem::propagateParentSelection(bool value)
{
    // If parent has a data model - determine its status
    if (dataModel) {
        // If propagating a true value - set it to true since at least one child will be checked
        if (value) {
            dataModel->setSelected(value);
        // Otherwise - go through all children to see if at least one child is checked
        } else {
            dataModel->setSelected(false);
            foreach(SelectionTreeItem *c, children) {
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

void SelectionTreeItem::propagateChildrenSelection(bool value)
{
    if (dataModel)
        dataModel->setSelected(value);

    for (int i = 0; i < children.length(); i++) {
        children.at(i)->propagateChildrenSelection(value);
    }
}

Selectable *SelectionTreeItem::getDataModel() const
{
    return dataModel;
}

QList<SelectionTreeItem *> SelectionTreeItem::getChildren() const
{
    return children;
}

void SelectionTreeItem::removeChild(int index)
{
    // TODO: Check if this is needed
    children.removeAt(index);
}
