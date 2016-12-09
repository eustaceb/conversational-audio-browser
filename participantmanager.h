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
    void on_toolButton_15_clicked();

signals:
    void notify_mainWindow_transcriptionFile(const QString &f);

private:
    Ui::ParticipantManager *ui;
};

#endif // PARTICIPANTMANAGER_H
