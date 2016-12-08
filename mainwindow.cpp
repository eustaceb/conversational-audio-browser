#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers.h"
#include "participantmanager.h"
#include "drawables/regulartimelinewidget.h"

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
    RegularTimelineWidget *t = new RegularTimelineWidget(this);

    ui->splitter->insertWidget(0, t);
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/justas/Dissertation/rand.wav"));
    player->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::on_actionParticipant_manager_triggered()
{
    ParticipantManager pm;
    pm.exec();
    pm.show();
}

void MainWindow::on_playButton_clicked()
{
    QString duration = QString::number(player->duration()/1000);
    QString current = QString::number(player->position()/1000);
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        ui->playButton->setText("Continue - " + current + "/" + duration);
    } else {
        player->play();
        ui->playButton->setText("Pause");
    }
}

void MainWindow::on_actionOpen_triggered()
{
    Transcription t = Helpers::parseTranscript("/home/justas/Dissertation/F01.trs");
}
