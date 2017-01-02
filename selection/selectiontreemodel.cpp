#include "selectiontreemodel.h"

SelectionTreeModel::SelectionTreeModel(SelectableTreeItem *root, QObject *parent)
    : root(root), QAbstractItemModel(parent)
{

}

SelectionTreeModel::~SelectionTreeModel()
{
    delete root;
}

QVariant SelectionTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    SelectableTreeItem *item = static_cast<SelectableTreeItem*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags SelectionTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

QVariant SelectionTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root->data(section);
    return QVariant();
}

QModelIndex SelectionTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    SelectableTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<SelectableTreeItem*>(parent.internalPointer());

    SelectableTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex SelectionTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    SelectableTreeItem *childItem = static_cast<SelectableTreeItem*>(index.internalPointer());
    SelectableTreeItem *parentItem = childItem->getParent();

    if (parentItem == root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int SelectionTreeModel::rowCount(const QModelIndex &parent) const
{
    SelectableTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<SelectableTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int SelectionTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return root->columnCount();
    else
        return static_cast<SelectableTreeItem*>(parent.internalPointer())->columnCount();
}
