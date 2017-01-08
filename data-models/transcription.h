#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <QList>

#include "selectable.h"
#include "filterable.h"

class Topic;
class Speaker;
class Recording;

class Transcription : public Selectable, public Filterable
{
public:
    Transcription(const QString &filename);
    virtual ~Transcription();

    void addTopic(Topic *t);
    void addSpeaker(Speaker *s);

    QList<Topic*> getTopics() const;
    void setTopics(const QList<Topic*> &value);

    QList<Speaker*> getSpeakers() const;
    void setSpeakers(const QList<Speaker*> &value);

    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;
    QString getFilename() const;

    Recording *getRecording() const;
    void setRecording(Recording *rec);

private:
    static int idCounter;
    int id;
    QString filename;
    Recording *recording;
    QList <Topic*> topics;
    QList <Speaker*> speakers;
};

#endif // TRANSCRIPTION_H
