#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <QList>
#include <topic.h>
#include <speaker.h>
#include <section.h>

class Transcription
{
public:
    Transcription();

    void addTopic(const Topic &t);
    void addSpeaker(const Speaker &s);
    void addSection(const Section &s);

    QList<Topic> getTopics() const;
    void setTopics(const QList<Topic> &value);

    QList<Speaker> getSpeakers() const;
    void setSpeakers(const QList<Speaker> &value);

    QList<Section> getSections() const;
    void setSections(const QList<Section> &value);

private:

    QList <Topic> topics;
    QList <Speaker> speakers;
    QList <Section> sections;
};

#endif // TRANSCRIPTION_H
