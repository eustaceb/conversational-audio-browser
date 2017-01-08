#include "filemanager.h"
#include "ui_filemanager.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>

FileManager::FileManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManager)
{
    ui->setupUi(this);
}

FileManager::~FileManager()
{
    delete ui;
}

void FileManager::on_annotationFileLookupButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Select a TRS transcription file"), "/home/justas/Dissertation", tr("TRS Files (*.trs)"));
    ui->annotationsFileLineEdit->setText(filename);
}

void FileManager::on_cancelOkButtonBox_accepted()
{
    // TODO: Save
    this->close();
}

void FileManager::on_cancelOkButtonBox_rejected()
{
    this->close();
}

void FileManager::on_loadFilesButton_clicked()
{
    QString annotationsFile = ui->annotationsFileLineEdit->text();
    QString audioFile = ui->audioFileLineEdit->text();
    if (annotationsFile != "")
        emit notify_mainWindow_filesLoaded(annotationsFile, audioFile);
}


void FileManager::on_audioFileLookupButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Select a WAV audio file"), "/home/justas/Dissertation", tr("WAV Audio Files (*.wav)"));
    ui->audioFileLineEdit->setText(filename);
}
