#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <QList>

#include "data-models/topic.h"
#include "data-models/speaker.h"
#include "data-models/section.h"

class Transcription
{
public:
    Transcription();
    ~Transcription();

    void addTopic(Topic *t);
    void addSpeaker(Speaker *s);
    void addSection(Section *s);

    QList<Topic*> getTopics() const;
    void setTopics(const QList<Topic*> &value);

    QList<Speaker*> getSpeakers() const;
    void setSpeakers(const QList<Speaker*> &value);

    QList<Section*> getSections() const;
    void setSections(const QList<Section*> &value);
private:
    //QStandardItemModel* tpc, spk, sec;
    // TODO: Topics -> Sections hierarchy
    QList <Topic*> topics;
    QList <Speaker*> speakers;
    QList <Section*> sections;
};

#endif // TRANSCRIPTION_H
