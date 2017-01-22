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

class TimelineWidget;
class MultiTimelineWidget;
class Transcription;
class SelectionTreeModel;
class FilterTreeModel;
class Statistics;
class FileManager;

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

    QMap<int, Transcription *> *getTranscriptions() const;

private slots:

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

    void on_multifileRadioButton_clicked();

    void on_simpleRadioButton_clicked();

    void on_transcriptionComboBox_currentIndexChanged(int index);

    void on_actionStatistics_triggered();

private:
    Ui::MainWindow *ui;
    Statistics *statistics;
    FileManager *fileManager;

    QMediaPlayer *player;

    QMap<int, Transcription *> *transcriptions;

    TimelineWidget *timeline;
    MultiTimelineWidget *multiTimeline;

    SelectionTreeModel *selectionTree;
    FilterTreeModel *filterTree;
};

#endif // MAINWINDOW_H
