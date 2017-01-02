#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <QList>

#include "data-models/topic.h"
#include "data-models/speaker.h"

class Transcription
{
public:
    Transcription();
    ~Transcription();

    void addTopic(Topic *t);
    void addSpeaker(Speaker *s);

    QList<Topic*> getTopics() const;
    void setTopics(const QList<Topic*> &value);

    QList<Speaker*> getSpeakers() const;
    void setSpeakers(const QList<Speaker*> &value);

private:
    QList <Topic*> topics;
    QList <Speaker*> speakers;
};

#endif // TRANSCRIPTION_H
