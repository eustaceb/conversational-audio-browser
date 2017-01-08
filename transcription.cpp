#include "transcription.h"

int Transcription::idCounter = 0;

Transcription::Transcription(const QString &filename)
{
    this->id = idCounter++;
    this->filename = filename;
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

QList<QVariant> Transcription::composeTreePayload() const
{
    QList<QVariant> payload;
    payload.append("trs" + QString::number(id));\
    QStringList splitFilename = filename.split("/");
    payload.append(splitFilename.at(splitFilename.length() - 1));
    payload.append("transcription");
    payload.append(QString::number(speakers.length()) + " speakers");
    return payload;
}

QString Transcription::getFilename() const
{
    return filename;
}
