#include "filtertreeitem.h"

FilterTreeItem::FilterTreeItem(Filterable *dataModel, FilterTreeItem *parent)
    : dataModel(dataModel), parent(parent)
{
    payload = dataModel->composeTreePayload();
}

FilterTreeItem::FilterTreeItem(const QList<QVariant> &data, FilterTreeItem *parent)
    : dataModel(0), parent(parent)
{
    payload = data;
}

FilterTreeItem::~FilterTreeItem()
{
    qDeleteAll(children);
}

void FilterTreeItem::appendChild(FilterTreeItem *item)
{
    children.append(item);
}

FilterTreeItem *FilterTreeItem::child(int index)
{
    return children.value(index);
}

int FilterTreeItem::childCount() const
{
    return children.length();
}

int FilterTreeItem::row() const
{
    if (parent)
        return parent->getChildren().indexOf(const_cast<FilterTreeItem*>(this));
    return 0;
}

FilterTreeItem *FilterTreeItem::getParent()
{
    return parent;
}

int FilterTreeItem::columnCount() const
{
    return payload.length();
}

QVariant FilterTreeItem::data(int column) const
{
    return payload.value(column);
}

bool FilterTreeItem::isFiltered() const
{
    return dataModel->isFiltered();
}

void FilterTreeItem::setFiltered(bool value)
{
    dataModel->setFiltered(value);
}

void FilterTreeItem::propagateFiltered(bool value)
{
    propagateChildrenFiltering(value);
    if (parent)
        parent->propagateParentFiltering(value);
}

void FilterTreeItem::propagateParentFiltering(bool value)
{
    // If parent has a data model - determine its status
    if (dataModel) {
        // If propagating a true value - set it to true since at least one child will be filtered
        if (value) {
            dataModel->setFiltered(value);
        // Otherwise - go through all children to see if at least one child is filtered
        } else {
            dataModel->setFiltered(false);
            foreach(FilterTreeItem *c, children) {
                if (c->isFiltered()) {
                    dataModel->setFiltered(true);
                    break;
                }
            }
        }
    }
    // Propagate up
    if (parent)
        parent->propagateParentFiltering(value);
}

void FilterTreeItem::propagateChildrenFiltering(bool value)
{
    if (dataModel)
        dataModel->setFiltered(value);

    for (int i = 0; i < children.length(); i++) {
        children.at(i)->propagateChildrenFiltering(value);
    }
}

Filterable *FilterTreeItem::getDataModel() const
{
    return dataModel;
}

QList<FilterTreeItem *> FilterTreeItem::getChildren() const
{
    return children;
}
