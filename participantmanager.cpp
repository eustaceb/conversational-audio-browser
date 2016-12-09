#include "participantmanager.h"
#include "ui_participantmanager.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>

ParticipantManager::ParticipantManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParticipantManager)
{
    ui->setupUi(this);
}

ParticipantManager::~ParticipantManager()
{
    delete ui;
}

void ParticipantManager::on_toolButton_15_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/justas/Dissertation", tr("TRS Files (*.trs)"));
    emit notify_mainWindow_transcriptionFile(filename);
}
