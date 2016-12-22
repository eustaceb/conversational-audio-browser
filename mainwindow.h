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
    void reloadWidgets(Transcription *transc);
    ~MainWindow();

private slots:
    void on_actionParticipant_manager_triggered();

    void when_transcription_loaded(const QString &filename);

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionSelect_Tool_triggered();

    void on_actionHand_Tool_triggered();

    void on_actionInspect_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    TimelineWidget *timeline;
    // TODO: Decide between list or some table structure with faster lookups
};

#endif // MAINWINDOW_H
