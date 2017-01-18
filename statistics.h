#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QMap>

namespace Ui {
class Statistics;
}

class SelectionTreeModel;
class FilterTreeModel;
class Transcription;

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QMap<int, Transcription *> *transcriptions,
                        SelectionTreeModel *selectionTree, FilterTreeModel *filterTree,
                        QWidget *parent = 0);
    ~Statistics();

private:
    Ui::Statistics *ui;

    QMap<int, Transcription *> *transcriptions;
    SelectionTreeModel *selectionTree;
    FilterTreeModel *filterTree;
};

#endif // STATISTICS_H
