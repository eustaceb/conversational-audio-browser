#include "mainwindow.h"
#include "filemanager.h"
#include "statistics.h"

#include "drawables/regular/timelinewidget.h"
#include "drawables/multifile/multitimelinewidget.h"

#include "data-models/transcription.h"
#include "data-models/recording.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    transcriptions = new QMap<int, Transcription*>();

    // Toolbar setup
    ui->toolBar->addWidget(ui->trackSlider);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(ui->controlsWidget);

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
    multiTimeline = new MultiTimelineWidget(transcriptions, this);
    when_transcription_loaded("/home/justas/Dissertation/F01.trs", "");
    ui->splitter->insertWidget(0, timeline);
    ui->splitter->insertWidget(1, multiTimeline);

    //multiTimeline->setVisible(false);

    // Audio setup
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/loomer.wav"));
    player->setVolume(50);

    // Trigger the Hand Tool and Simple Timeline by default
    on_actionHand_Tool_triggered();
    ui->simpleRadioButton->click();
}


MainWindow::~MainWindow()
{
    delete selectionTree;
    delete filterTree;
    qDeleteAll((*transcriptions));
    delete transcriptions;
    delete timeline;
    delete player;
    delete ui;
}

void MainWindow::on_actionParticipant_manager_triggered()
{
    FileManager *p = new FileManager;
    connect(p, SIGNAL(notify_mainWindow_filesLoaded(QString, QString)),
            this, SLOT(when_transcription_loaded(QString, QString)));
    p->exec();
}

void MainWindow::when_transcription_loaded(const QString &annotationsFile, const QString &audioFile)
{
    foreach(Transcription *t, (*transcriptions)) {
        if (t->getFilepath() == annotationsFile) {
            QMessageBox messageBox;
            messageBox.setText("Unable to load " + annotationsFile + " - it is already loaded.");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.exec();
            return;
        }
    }

    Transcription *trs = Helpers::parseTranscript(annotationsFile);
    if (audioFile != "")
        trs->setRecording(new Recording(audioFile));
    transcriptions->insert(trs->getId(), trs);

    // Update selection/filter trees
    selectionTree->appendTranscription(trs);
    filterTree->appendTranscription(trs);

    // Update toolbar
    ui->transcriptionComboBox->clear();
    foreach (Transcription *t, (*transcriptions)) {
        ui->transcriptionComboBox->addItem(t->getFilename(), t->getId());
    }
    int comboBoxIndex = ui->transcriptionComboBox->findData(trs->getId());
    if (comboBoxIndex != -1)
            ui->transcriptionComboBox->setCurrentIndex(comboBoxIndex);

    multiTimeline->reloadScene();

    // Alert success
    QMessageBox messageBox;
    messageBox.setText("File(s) have been successfully loaded.");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();

}

void MainWindow::on_actionOpen_triggered()
{
    FileManager *p = new FileManager;
    connect(p, SIGNAL(notify_mainWindow_filesLoaded(QString, QString)),
            this, SLOT(when_transcription_loaded(QString, QString)));
    p->exec();
    // TODO: Leak, Qt::WDestructiveClose ?
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

QMap<int, Transcription *> *MainWindow::getTranscriptions() const
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

void MainWindow::on_multifileRadioButton_clicked()
{
    multiTimeline->reloadScene();
    ui->transcriptionComboBox->setEnabled(false);
    timeline->setVisible(false);
    multiTimeline->setVisible(true);
}

void MainWindow::on_simpleRadioButton_clicked()
{
    ui->transcriptionComboBox->setEnabled(true);
    multiTimeline->setVisible(false);
    timeline->setVisible(true);
}

void MainWindow::on_transcriptionComboBox_currentIndexChanged(int index)
{
    int id = ui->transcriptionComboBox->itemData(index).toInt();
    Transcription *trs = transcriptions->find(id).value();
    timeline->setTranscription(trs);
    timeline->reloadScene();
}

void MainWindow::on_actionStatistics_triggered()
{
    Statistics *s = new Statistics;
    s->show();
    // TODO: Leak, Qt::WDestructiveClose ?
}
