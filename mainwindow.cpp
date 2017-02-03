#include "mainwindow.h"
#include "filemanager.h"
#include "statistics.h"

#include "drawables/regular/timelinewidget.h"
#include "drawables/multifile/multitimelinewidget.h"

#include "data-models/transcription.h"
#include "data-models/recording.h"

#include "trees/filtertreemodel.h"
#include "trees/selectiontreemodel.h"

#include "statistics.h"
#include "filemanager.h"
#include "slicer.h"

#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    transcriptions = new QMap<int, Transcription*>();

    // Toolbar setup
    ui->audioControls->hide();
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);
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

    // Status bar
    cursorPosLabel = new QLabel(QString::number(timeline->getCursor().x()));
    ui->statusBar->addPermanentWidget(cursorPosLabel);
    connect(timeline, SIGNAL(mouseMoved()), this, SLOT(when_mouse_moved()));

    // Filemanager setup
    fileManager = new FileManager;
    connect(fileManager, SIGNAL(notify_mainWindow_filesLoaded(QString, QString)),
            this, SLOT(when_transcription_loaded(QString, QString)));

    // Statistics setup
    statistics = new Statistics(transcriptions);
    connect(filterTree, SIGNAL(treeUpdated()), statistics, SLOT(generateGeneralModel()));
    connect(selectionTree, SIGNAL(treeUpdated()), statistics, SLOT(generateGeneralModel()));

    // Slicer setup
    slicer = new Slicer(transcriptions);
    connect(filterTree, SIGNAL(treeUpdated()), slicer, SLOT(recalculateFileCount()));
    connect(selectionTree, SIGNAL(treeUpdated()), slicer, SLOT(recalculateFileCount()));

    // Audio setup
    player = new QMediaPlayer;
    duration = 0;
    player->setVolume(50);

    connect(ui->trackSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(mediaErrorMessage()));

    // Trigger the Hand Tool and Simple Timeline by default
    on_actionHand_Tool_triggered();
    ui->simpleRadioButton->click();
}


MainWindow::~MainWindow()
{
    delete statistics;
    delete slicer;
    delete fileManager;
    delete selectionTree;
    delete filterTree;
    qDeleteAll((*transcriptions));
    delete transcriptions;
    delete timeline;
    delete player;
    delete ui;
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
        ui->transcriptionComboBox->addItem(t->getFilename(), QVariant(t->getId()));
    }

    int comboBoxIndex = ui->transcriptionComboBox->findData(QVariant(trs->getId()));

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
    fileManager->show();
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

void MainWindow::mediaErrorMessage()
{
    QMessageBox messageBox;
    messageBox.setText(player->errorString());
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.exec();
}

void MainWindow::durationChanged(qint64 d)
{
    duration = d;
    ui->trackSlider->setMaximum(duration / 1000);
}

void MainWindow::positionChanged(qint64 pos)
{
    if (!ui->trackSlider->isSliderDown())
        ui->trackSlider->setValue(pos / 1000);

    QString currentStr = "00:00:00", totalStr = "00:00:00";
    if (pos || duration) {
        QTime current((pos / 3600000 ) % 60, (pos / 60000) % 60, (pos / 1000) % 60, pos % 1000);
        QTime total((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60, duration % 1000);
        QString format = "mm:ss";
        if (duration > 3600000)
            format = "hh:mm:ss";
        currentStr = current.toString(format);
        totalStr = total.toString(format);
    }
    ui->currentPosLineEdit->setText(currentStr);
    ui->totalPosLineEdit->setText(totalStr);
}

void MainWindow::seek(int where)
{
    player->setPosition(where * 1000);
}

void MainWindow::when_mouse_moved()
{
    cursorPosLabel->setText("Cursor at " + QString::number(timeline->getCursor().x()/10 + 20) + "s");
    ui->statusBar->update();
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
    cursorPosLabel->setText("");
    ui->audioControls->hide();
}

void MainWindow::on_simpleRadioButton_clicked()
{
    ui->transcriptionComboBox->setEnabled(true);
    multiTimeline->setVisible(false);
    timeline->setVisible(true);
    Transcription *t = transcriptions->find(ui->transcriptionComboBox->currentData().toInt()).value();
    if (t->getRecording() != 0)
        ui->audioControls->show();
}

void MainWindow::on_transcriptionComboBox_currentIndexChanged(int index)
{
    int id = ui->transcriptionComboBox->itemData(index).toInt();
    Transcription *trs = transcriptions->find(id).value();
    if (trs->getRecording() != 0) {
        player->setMedia(QUrl::fromLocalFile(trs->getRecording()->getFilename()));
        ui->audioControls->show();
    } else {
        ui->audioControls->hide();
    }
    timeline->setTranscription(trs);
    timeline->reloadScene();
}

void MainWindow::on_actionStatistics_triggered()
{
    statistics->show();
}

void MainWindow::on_playButton_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        ui->playButton->setIcon(QIcon(":/toolbar/icons/play"));
        player->pause();
    } else {
        ui->playButton->setIcon(QIcon(":/toolbar/icons/pause"));
        player->play();
    }
}

void MainWindow::on_actionSlicer_triggered()
{
    slicer->show();
}
