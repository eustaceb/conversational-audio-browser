#ifndef SLICER_H
#define SLICER_H

#include <QWidget>

namespace Ui {
class Slicer;
}

class Transcription;
class Section;
class Turn;

class Slicer : public QWidget
{
    Q_OBJECT

public:
    explicit Slicer(QMap<int, Transcription *> *transcriptions, QWidget *parent = 0);
    ~Slicer();

private slots:
    void on_cancelButton_clicked();

    void on_sliceButton_clicked();

    void on_currentSelectionRadioButton_clicked();

    void on_sectionsRadioButton_clicked();

    void on_everythingRadioButton_clicked();

    void on_turnsRadioButton_clicked();

    void recalculateFileCount();

private:
    Ui::Slicer *ui;

    QMap<int, Transcription *> *transcriptions;
};

#endif // SLICER_H
