#include "filtertreemodel.h"


FilterTreeModel::FilterTreeModel(FilterTreeItem *root, QObject *parent)
    : root(root), QAbstractItemModel(parent)
{

}

FilterTreeModel::~FilterTreeModel()
{
    delete root;
}

QVariant FilterTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    FilterTreeItem *item = static_cast<FilterTreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
        return static_cast<int>(item->isFiltered() ? Qt::Checked : Qt::Unchecked);

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

Qt::ItemFlags FilterTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 0) {
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}

QVariant FilterTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root->data(section);
    return QVariant();
}

QModelIndex FilterTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FilterTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<FilterTreeItem*>(parent.internalPointer());

    FilterTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex FilterTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    FilterTreeItem *childItem = static_cast<FilterTreeItem*>(index.internalPointer());
    FilterTreeItem *parentItem = childItem->getParent();

    if (parentItem == root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int FilterTreeModel::rowCount(const QModelIndex &parent) const
{
    FilterTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<FilterTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int FilterTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return root->columnCount();
    else
        return static_cast<FilterTreeItem*>(parent.internalPointer())->columnCount();
}

bool FilterTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::CheckStateRole)
        return false;

    FilterTreeItem *item = getItem(index);

    item->setFiltered(value.toBool());

    emit dataChanged(QModelIndex(), QModelIndex());

    return true;
}

FilterTreeItem *FilterTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        FilterTreeItem *item = static_cast<FilterTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return root;
}