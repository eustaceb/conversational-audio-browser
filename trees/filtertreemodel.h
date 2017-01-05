#ifndef FILTERTREEMODEL_H
#define FILTERTREEMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "filtertreeitem.h"

class Transcription;

class FilterTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FilterTreeModel(QObject *parent = 0);
    ~FilterTreeModel();

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

    void selectAll();
    void selectNone();
    void appendTranscription(Transcription *trs);

signals:
    void treeUpdated();

public slots:
    void refresh();

private:
    FilterTreeItem *getItem(const QModelIndex &index) const;

    FilterTreeItem *root;
};

#endif // FILTERTREEMODEL_H
