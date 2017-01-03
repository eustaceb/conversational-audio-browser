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
#include "participantmanager.h"
#include "drawables/regular/timelinewidget.h"


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

    QList<SelectableTreeItem *> getSelection() const;

private slots:
    void on_actionParticipant_manager_triggered();

    void when_transcription_loaded(const QString &filename);

    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionSelect_Tool_triggered();

    void on_actionHand_Tool_triggered();

    void selection_updated();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    TimelineWidget *timeline;

    SelectionTreeModel *selectionTree;
    QList<SelectableTreeItem*> selection;
};

#endif // MAINWINDOW_H
