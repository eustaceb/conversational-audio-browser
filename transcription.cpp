#include "transcription.h"

Transcription::Transcription()
{

}

Transcription::~Transcription()
{
    qDeleteAll(speakers);
    qDeleteAll(topics);
    qDeleteAll(sections);
}

void Transcription::addTopic(Topic *t)
{
    this->topics.append(t);
}

void Transcription::addSpeaker(Speaker *speaker)
{
    this->speakers.append(speaker);
}

void Transcription::addSection(Section *s)
{
    this->sections.append(s);
}

QList<Topic*> Transcription::getTopics() const
{
    return topics;
}

void Transcription::setTopics(const QList<Topic*> &value)
{
    topics = value;
}

QList<Speaker*> Transcription::getSpeakers() const
{
    return speakers;
}

void Transcription::setSpeakers(const QList<Speaker*> &value)
{
    speakers = value;
}

QList<Section*> Transcription::getSections() const
{
    return sections;
}

void Transcription::setSections(const QList<Section*> &value)
{
    sections = value;
}
