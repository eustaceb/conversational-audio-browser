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

void ParticipantManager::on_annotationFileLookupButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/justas/Dissertation", tr("TRS Files (*.trs)"));
    ui->annotationsFileLine->setText(filename);
}

void ParticipantManager::on_cancelOkButtonBox_accepted()
{
    // TODO: Save
    this->close();
}

void ParticipantManager::on_cancelOkButtonBox_rejected()
{
    this->close();
}

void ParticipantManager::on_loadFilesButton_clicked()
{
    QString filename = ui->annotationsFileLine->text();
    if (filename != "")
        emit notify_mainWindow_transcriptionFile(filename);
}
