#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    Transcription *trs = Helpers::parseTranscript("/home/justas/Dissertation/F01.trs");

    timeline = new TimelineWidget(trs, this);

    // Selection tree
    selectionTree = Helpers::generateSelectionTree(trs);
    ui->selectionTreeView->setModel(selectionTree);
    // Connect the selection tree
    connect(selectionTree, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(selection_updated()));
    // Filter tree
    filterTree = Helpers::generateFilterTree(trs);
    ui->filterTreeView->setModel(filterTree);
    // Connect the filter tree
    connect(filterTree, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(selection_updated()));
    // Connect the selection tree with the filter tree
    connect(filterTree, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            selectionTree, SLOT(refresh()));

    reloadWidgets(trs);

    // Trigger the Hand Tool by default
    on_actionHand_Tool_triggered();

    // Audio setup
    ui->splitter->insertWidget(0, timeline);
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/loomer.wav"));
    player->setVolume(50);
}

void MainWindow::reloadWidgets(Transcription *transc)
{
    Q_UNUSED(transc);
}

MainWindow::~MainWindow()
{
    delete selectionTree;
    delete player;
    delete timeline;
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
    Transcription *trs = Helpers::parseTranscript(filename);
    reloadWidgets(trs);
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
