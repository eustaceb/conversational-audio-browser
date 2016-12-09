#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

#include <QtMultimedia/QMediaPlayer>

#include <drawables/regular/timelinewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionParticipant_manager_triggered();

    void on_transcriptionFile_loaded(const QString &filename);

    void on_playButton_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    TimelineWidget *timeline;
};

#endif // MAINWINDOW_H
