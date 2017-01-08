#ifndef PARTICIPANTMANAGER_H
#define PARTICIPANTMANAGER_H

#include <QDialog>

namespace Ui {
class FileManager;
}

class FileManager : public QDialog
{
    Q_OBJECT

public:
    explicit FileManager(QWidget *parent = 0);
    ~FileManager();

private slots:
    void on_annotationFileLookupButton_clicked();

    void on_cancelOkButtonBox_accepted();

    void on_cancelOkButtonBox_rejected();

    void on_loadFilesButton_clicked();

    void on_audioFileLookupButton_clicked();

signals:
    void notify_mainWindow_filesLoaded(const QString &annotationsFile, const QString &audioFile);

private:
    Ui::FileManager *ui;
};

#endif // PARTICIPANTMANAGER_H
