#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QSignalMapper>
#include <QList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QListView>
#include <QtMultimedia/QMediaPlayer>

#include "ui_mainwindow.h"
#include "helpers.h"
#include "filemanager.h"
#include "drawables/regular/timelinewidget.h"

class Transcription;

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

    QList<Transcription *> getTranscriptions() const;

private slots:
    void on_actionParticipant_manager_triggered();

    void when_transcription_loaded(const QString &annotationsFile, const QString &audioFile);

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionSelect_Tool_triggered();

    void on_actionHand_Tool_triggered();

    void selection_updated();
    void on_selectAllButton_clicked();

    void on_selectNoneButton_clicked();

    void on_filterAllButton_clicked();

    void on_filterNoneButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;

    QList<Transcription *> transcriptions;

    TimelineWidget *timeline;

    SelectionTreeModel *selectionTree;
    FilterTreeModel *filterTree;
};

#endif // MAINWINDOW_H
