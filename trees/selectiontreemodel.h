#ifndef SELECTIONTREEMODEL_H
#define SELECTIONTREEMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "selectiontreeitem.h"

class SelectionTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SelectionTreeModel(SelectionTreeItem *root, QObject *parent = 0);
    ~SelectionTreeModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

public slots:
    void refresh();

private:
    SelectionTreeItem *getItem(const QModelIndex &index) const;

    SelectionTreeItem *root;
};

#endif // SELECTIONTREEMODEL_H
