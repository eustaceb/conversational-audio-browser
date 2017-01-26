#ifndef SLICER_H
#define SLICER_H

#include <QWidget>

namespace Ui {
class Slicer;
}

class Slicer : public QWidget
{
    Q_OBJECT

public:
    explicit Slicer(QWidget *parent = 0);
    ~Slicer();

private:
    Ui::Slicer *ui;
};

#endif // SLICER_H
