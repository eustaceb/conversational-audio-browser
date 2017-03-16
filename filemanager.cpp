#include "filemanager.h"
#include "ui_filemanager.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
    if (ui->annotationsFileLineEdit->text() != "")
        on_loadFilesButton_clicked();
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
    if (annotationsFile != "") {
        emit notify_mainWindow_filesLoaded(annotationsFile, audioFile);
        ui->annotationsFileLineEdit->clear();
        ui->audioFileLineEdit->clear();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Please select an annotations file.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void FileManager::on_audioFileLookupButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Select a WAV audio file"), "/home/justas/Dissertation", tr("WAV Audio Files (*.wav)"));
    ui->audioFileLineEdit->setText(filename);
}
