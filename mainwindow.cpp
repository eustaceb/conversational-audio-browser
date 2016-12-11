#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers.h"
#include "participantmanager.h"
#include "drawables/regular/timelinewidget.h"

#include <QtMultimedia/QMediaPlayer>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->timelineView;

    Transcription trs = Helpers::parseTranscript("/home/justas/Dissertation/F01.trs");

    timeline = new TimelineWidget(trs, this);

    ui->splitter->insertWidget(0, timeline);
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/loomer.wav"));
    player->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete player;
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
    Transcription trs = Helpers::parseTranscript(filename);

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
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::on_action_Tool_triggered()
{
    timeline->triggerTool();
}
