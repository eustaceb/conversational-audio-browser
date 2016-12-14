#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers.h"
#include "participantmanager.h"
#include "drawables/regular/timelinewidget.h"

#include <QtMultimedia/QMediaPlayer>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    Transcription *trs = Helpers::parseTranscript("/home/justas/Dissertation/F01.trs");

    timeline = new TimelineWidget(trs, this);
    reloadWidgets(trs);

    // Trigger the Hand Tool by default
    on_actionHand_Tool_triggered();

    ui->splitter->insertWidget(0, timeline);
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/loomer.wav"));
    player->setVolume(50);
}

void MainWindow::reloadWidgets(Transcription *transc)
{
    ui->speakerListWidget->clear();
    ui->topicListWidget->clear();
    // TODO: Replace with models / ListView
    foreach(Speaker* s, transc->getSpeakers()) {
        ui->speakerListWidget->addItem(s->getName());
    }
    foreach(const Topic &t, transc->getTopics()) {
        ui->topicListWidget->addItem(t.getDesc());
    }
}

MainWindow::~MainWindow()
{
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
    //p->show();
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
    ui->actionInterval_Select->setChecked(false);
}

void MainWindow::on_actionHand_Tool_triggered()
{
    timeline->setTool(TimelineWidget::HandTool);
    timeline->setCursor(Qt::OpenHandCursor);

    ui->actionHand_Tool->setChecked(true);
    ui->actionInterval_Select->setChecked(false);
    ui->actionSelect_Tool->setChecked(false);
}

void MainWindow::on_actionInterval_Select_triggered()
{
    timeline->setTool(TimelineWidget::IntervalSelectTool);
    timeline->setCursor(Qt::IBeamCursor);

    ui->actionInterval_Select->setChecked(true);
    ui->actionHand_Tool->setChecked(false);
    ui->actionSelect_Tool->setChecked(false);
}
