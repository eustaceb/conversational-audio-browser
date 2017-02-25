#include "mainwindow.h"
#include "filemanager.h"
#include "statistics.h"

#include "drawables/regular/timelinewidget.h"
#include "drawables/multifile/multitimelinewidget.h"

#include "data-models/transcription.h"
#include "data-models/recording.h"
#include "data-models/section.h"

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
    connect(ui->syncTimelineBox, SIGNAL(stateChanged(int)), timeline, SLOT(syncCheckBox(int)));
    multiTimeline = new MultiTimelineWidget(transcriptions, this);
    //when_transcription_loaded("/home/justas/Dissertation/F01.trs", "");
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
    ui->trackSlider->setRange(0, 0);

    connect(ui->trackSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int))); // TODO: Problem
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64))); // TODO: Problem
    connect(player, SIGNAL(positionChanged(qint64)), timeline, SLOT(syncPosition(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(mediaErrorMessage()));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), timeline, SLOT(playerStateChanged(QMediaPlayer::State)));

    ui->simpleRadioButton->click();
    fileManager->show();
    fileManager->activateWindow();
    fileManager->raise();
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
    ui->trackSlider->setRange(0, duration / 1000);
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
    int s = timeline->getCursor().x()/10 + 20;
    if (s < 0) s = 0;
    QString minutesAndSeconds = QString::number((s / 60)) + "'" + QString::number((s % 60));
    cursorPosLabel->setText("Cursor at " + QString::number(s) + "s (" + minutesAndSeconds + ")");
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
    ui->noAudioFileLoaded->hide();
    ui->audioControls->hide();
    // Reset timeline / selection splitter
    ui->splitter->setSizes(QList<int>({0, 200, 200}));
}

void MainWindow::on_simpleRadioButton_clicked()
{
    ui->transcriptionComboBox->setEnabled(true);
    multiTimeline->setVisible(false);
    timeline->setVisible(true);
    if (transcriptions->find(ui->transcriptionComboBox->currentData().toInt()) != transcriptions->end()) {
        Transcription *t = transcriptions->find(ui->transcriptionComboBox->currentData().toInt()).value();
        if (t->getRecording() != 0) {
            ui->noAudioFileLoaded->hide();
            ui->audioControls->show();
        }
        else
            ui->noAudioFileLoaded->show();
    }
    // Reset timeline / selection splitter
    ui->splitter->setSizes(QList<int>({200, 0, 200}));
}

void MainWindow::on_transcriptionComboBox_currentIndexChanged(int index)
{
    if (index == -1) {
        ui->audioControls->hide();
        ui->noAudioFileLoaded->show();
        timeline->setTranscription(0);
    } else {
        int id = ui->transcriptionComboBox->itemData(index).toInt();
        Transcription *trs = transcriptions->find(id).value();
        if (trs->getRecording() != 0) {
            player->setMedia(QUrl::fromLocalFile(trs->getRecording()->getFilename()));
            ui->noAudioFileLoaded->hide();
            ui->audioControls->show();
        } else {
            ui->audioControls->hide();
            ui->noAudioFileLoaded->show();
        }
        timeline->setTranscription(trs);
    }
    timeline->reloadScene();
}

void MainWindow::on_actionStatistics_triggered()
{
    statistics->show();
}

void MainWindow::on_playButton_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::on_actionSlicer_triggered()
{
    slicer->show();
}

void MainWindow::on_prevSectionButton_clicked()
{
    int id = ui->transcriptionComboBox->currentData().toInt();
    Transcription *trs = transcriptions->find(id).value();

    Section *min = 0;
    foreach (Section *s, trs->getSectionList()) {
        if ((s->getEndTime() * 1000 <= player->position() && min == 0)
            || (min != 0 && s->getEndTime() * 1000 < player->position() && s->getEndTime() > min->getEndTime()))
            min = s;
    }

    if (min != 0) {
        player->setPosition(min->getEndTime() * 1000 - 250);
    } else {
        player->setPosition(0);
    }
}

void MainWindow::on_nextSectionButton_clicked()
{
    int id = ui->transcriptionComboBox->currentData().toInt();
    Transcription *trs = transcriptions->find(id).value();

    foreach (Section *s, trs->getSectionList()) {
        if (s->getEndTime() * 1000 > player->position() && player->position() > s->getStartTime() * 1000) {
            player->setPosition(s->getEndTime() * 1000);
            return;
        }
    }
}

void MainWindow::on_actionResize_timeline_triggered()
{
    if (ui->multifileRadioButton->isChecked()) { // Multifile timeline
        if (ui->splitter->sizes()[2] == 0) { // Already maximized - minimize
            ui->splitter->setSizes(QList<int>({0, 200, 200}));
        } else {
            ui->splitter->setSizes(QList<int>({0, 200, 0}));
        }
    } else { // Simple timeline
        if (ui->splitter->sizes()[2] == 0) { // Already maximized - minimize
            ui->splitter->setSizes(QList<int>({200, 0, 200}));
        } else {
            ui->splitter->setSizes(QList<int>({200, 0, 0}));
        }
    }
}

void MainWindow::on_toolButton_clicked()
{
    if (!player->isMuted())
        player->setMuted(true);
    else
        player->setMuted(false);
}

void MainWindow::on_closeTranscriptionButton_clicked()
{
    if (transcriptions->find(ui->transcriptionComboBox->currentData().toInt()) != transcriptions->end()) {
        Transcription *trs = transcriptions->find(ui->transcriptionComboBox->currentData().toInt()).value();
        // Update selection/filter trees
        selectionTree->removeTranscription(trs);
        filterTree->removeTranscription(trs);
        transcriptions->remove(trs->getId());
        // Update toolbar
        ui->transcriptionComboBox->clear();

        foreach (Transcription *t, (*transcriptions)) {
            ui->transcriptionComboBox->addItem(t->getFilename(), QVariant(t->getId()));
        }

        delete trs;
        multiTimeline->reloadScene();
    }
}
