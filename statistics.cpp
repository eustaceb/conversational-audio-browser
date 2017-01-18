#include "statistics.h"
#include "ui_statistics.h"

#include "data-models/transcription.h"
#include "trees/filtertreemodel.h"
#include "trees/filtertreeitem.h"
#include "trees/selectiontreemodel.h"
#include "trees/selectiontreeitem.h"


Statistics::Statistics(QMap<int, Transcription *> *transcriptions,
                       SelectionTreeModel *selectionTree, FilterTreeModel *filterTree,
                       QWidget *parent) :
    transcriptions(transcriptions),
    selectionTree(selectionTree),
    filterTree(filterTree),
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
}

Statistics::~Statistics()
{
    delete ui;
}
