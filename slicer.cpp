#include "slicer.h"
#include "ui_slicer.h"

Slicer::Slicer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slicer)
{
    ui->setupUi(this);
}

Slicer::~Slicer()
{
    delete ui;
}
