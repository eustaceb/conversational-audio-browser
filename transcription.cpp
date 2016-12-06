#include "transcription.h"

Transcription::Transcription()
{

}

void Transcription::addTopic(const Topic &t)
{
    this->topics.append(t);
}

void Transcription::addSpeaker(const Speaker &p)
{
    this->speakers.append(p);
}

void Transcription::addSection(const Section &s)
{
    this->sections.append(s);
}

QList<Topic> Transcription::getTopics() const
{
    return topics;
}

void Transcription::setTopics(const QList<Topic> &value)
{
    topics = value;
}

QList<Speaker> Transcription::getSpeakers() const
{
    return speakers;
}

void Transcription::setSpeakers(const QList<Speaker> &value)
{
    speakers = value;
}

QList<Section> Transcription::getSections() const
{
    return sections;
}

void Transcription::setSections(const QList<Section> &value)
{
    sections = value;
}
