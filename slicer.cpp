#include "slicer.h"
#include "ui_slicer.h"

#include "data-models/transcription.h"
#include "data-models/topic.h"
#include "data-models/section.h"
#include "data-models/speaker.h"
#include "data-models/turn.h"
#include "data-models/recording.h"

#include <QMessageBox>
#include <QFileDialog>

Slicer::Slicer(QMap<int, Transcription *> *transcriptions, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slicer),
    transcriptions(transcriptions)
{
    ui->setupUi(this);
    recalculateFileCount();
}

Slicer::~Slicer()
{
    delete ui;
}

void Slicer::on_cancelButton_clicked()
{
    this->hide();
}

void Slicer::on_sliceButton_clicked()
{
    QMessageBox msgBox;
    bool selected = ui->currentSelectionRadioButton->isChecked();
    bool sections = ui->sectionsRadioButton->isChecked();

    QString prefix = QFileDialog::getSaveFileName(this, "Select prefix and location for exported files", "/", "Any (*.*)");
    if (prefix == "") return;
    foreach (Transcription *t, (*transcriptions)) {
        if (t->getRecording() == 0) continue;
        QString filename = prefix + "-" + t->getTitle();
        if (sections) {
            filename += "-section-";
            foreach (Section *s, t->getSectionList(selected)) {
                QString fullFilename = filename + QString::number(s->getId()) + "-" + s->getTopic()->getDesc() + ".wav";
                int result = t->getRecording()->sliceOut(s->getStartTime(), s->getEndTime(), fullFilename);
                if (result != 0) {
                    msgBox.setText("Something went wrong. Could not slice audio files. Error " + QString::number(result));
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.exec();
                    return;
                }
            }
        } else {
            filename += "-turn-";
            foreach (Turn *trn, t->getTurnList(selected)) {
                QString fullFilename = filename + QString::number(trn->getId()) + "-" + trn->getSpeaker()->getName() + ".wav";
                int result = t->getRecording()->sliceOut(trn->getStartTime(), trn->getEndTime(), fullFilename);
                if (result != 0) {
                    msgBox.setText("Something went wrong. Could not slice audio files. Error " + QString::number(result));
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.exec();
                    return;
                }
            }
        }
    }
    msgBox.setText("File(s) have been successfully exported.");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void Slicer::recalculateFileCount()
{
    bool selected = ui->currentSelectionRadioButton->isChecked();
    bool sections = ui->sectionsRadioButton->isChecked();

    int count = 0;

    foreach (Transcription *t, (*transcriptions)) {
        if (t->getRecording() == 0) continue;
        if (sections)
            count += t->getSectionList(selected).size();
        else
            count += t->getTurnList(selected).size();
    }
    ui->resultCountLineEdit->setText(QString::number(count));
}

void Slicer::on_currentSelectionRadioButton_clicked()
{
    recalculateFileCount();
}

void Slicer::on_sectionsRadioButton_clicked()
{
    recalculateFileCount();
}

void Slicer::on_everythingRadioButton_clicked()
{
    recalculateFileCount();
}

void Slicer::on_turnsRadioButton_clicked()
{
    recalculateFileCount();
}
