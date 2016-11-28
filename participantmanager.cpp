#include "participantmanager.h"
#include "ui_participantmanager.h"

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
