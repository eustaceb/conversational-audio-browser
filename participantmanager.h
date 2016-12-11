#ifndef PARTICIPANTMANAGER_H
#define PARTICIPANTMANAGER_H

#include <QDialog>

namespace Ui {
class ParticipantManager;
}

class ParticipantManager : public QDialog
{
    Q_OBJECT

public:
    explicit ParticipantManager(QWidget *parent = 0);
    ~ParticipantManager();

private slots:
    void on_annotationFileLookupButton_clicked();

    void on_cancelOkButtonBox_accepted();

    void on_cancelOkButtonBox_rejected();

    void on_loadFilesButton_clicked();

signals:
    void notify_mainWindow_transcriptionFile(const QString &filename);

private:
    Ui::ParticipantManager *ui;
};

#endif // PARTICIPANTMANAGER_H
