#include "transcription.h"

Transcription::Transcription()
{

}

Transcription::~Transcription()
{
    qDeleteAll(speakers);
    qDeleteAll(topics);
}

void Transcription::addTopic(Topic *t)
{

    this->topics.append(t);
}

void Transcription::addSpeaker(Speaker *speaker)
{
    this->speakers.append(speaker);
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
