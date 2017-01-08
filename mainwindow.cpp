#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    // Selection tree
    selectionTree = new SelectionTreeModel;
    ui->selectionTreeView->setModel(selectionTree);
    // Connect the selection tree
    connect(selectionTree, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(selection_updated()));
    // Filter tree
    filterTree = new FilterTreeModel;
    ui->filterTreeView->setModel(filterTree);
    // Connect the filter tree
    connect(filterTree, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(selection_updated()));
    // Connect the two trees with each other
    connect(filterTree, SIGNAL(treeUpdated()), selectionTree, SLOT(refresh()));
    connect(selectionTree, SIGNAL(treeUpdated()), filterTree, SLOT(refresh()));

    // Timeline setup
    timeline = new TimelineWidget(this);
    when_transcription_loaded("/home/justas/Dissertation/F01.trs");
    ui->splitter->insertWidget(0, timeline);

    // Audio setup
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/loomer.wav"));
    player->setVolume(50);

    // Trigger the Hand Tool by default
    on_actionHand_Tool_triggered();
}


MainWindow::~MainWindow()
{
    delete selectionTree;
    delete filterTree;
    qDeleteAll(transcriptions);
    delete timeline;
    delete player;
    delete ui;
}

void MainWindow::on_actionParticipant_manager_triggered()
{
    ParticipantManager *p = new ParticipantManager;
    connect(p, SIGNAL(notify_mainWindow_transcriptionFile(QString)),
            this, SLOT(when_transcription_loaded(QString)));
    p->exec();
}

void MainWindow::when_transcription_loaded(const QString &filename)
{
    foreach(Transcription *t, transcriptions) {
        if (t->getFilename() == filename) {
            qInfo() << "Transcription already loaded.";
            return;
        }
    }

    Transcription *trs = Helpers::parseTranscript(filename);
    transcriptions.append(trs);

    selectionTree->appendTranscription(trs);
    filterTree->appendTranscription(trs);

    timeline->setTranscription(trs);
    timeline->reloadScene();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionPlay_triggered()
{
    QString duration = QString::number(player->duration()/1000);
    QString current = QString::number(player->position()/1000);
    // TODO: Set the play marker to the sound position
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::on_actionSelect_Tool_triggered()
{
    timeline->setTool(TimelineWidget::SelectTool);
    timeline->setCursor(Qt::ArrowCursor);

    ui->actionSelect_Tool->setChecked(true);
    ui->actionHand_Tool->setChecked(false);
}

void MainWindow::on_actionHand_Tool_triggered()
{
    timeline->setTool(TimelineWidget::HandTool);
    timeline->setCursor(Qt::OpenHandCursor);

    ui->actionHand_Tool->setChecked(true);
    ui->actionSelect_Tool->setChecked(false);
}

void MainWindow::selection_updated()
{
    timeline->viewport()->repaint();
}

QList<Transcription *> MainWindow::getTranscriptions() const
{
    return transcriptions;
}

void MainWindow::on_selectAllButton_clicked()
{
    selectionTree->selectAll();
}

void MainWindow::on_selectNoneButton_clicked()
{
    selectionTree->selectNone();
}

void MainWindow::on_filterAllButton_clicked()
{
    filterTree->selectAll();
}

void MainWindow::on_filterNoneButton_clicked()
{
    filterTree->selectNone();
}
