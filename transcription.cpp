#include "data-models/transcription.h"
#include "data-models/topic.h"
#include "data-models/speaker.h"
#include "data-models/recording.h"
#include "data-models/turn.h"

#include "helpers.h"

int Transcription::idCounter = 0;

Transcription::Transcription(const QString &filepath)
{
    this->id = idCounter++;
    this->filepath = filepath;
    QStringList splitFilepath = filepath.split("/");
    this->filename = splitFilepath.at(splitFilepath.length() - 1);
}

Transcription::~Transcription()
{
    qDeleteAll(speakers);
    qDeleteAll(topics);
    delete recording;
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
    payload.append(filename);
    payload.append("transcription");
    payload.append(QString::number(speakers.length()) + " speakers");
    return payload;
}

QString Transcription::getFilepath() const
{
    return filepath;
}

Recording *Transcription::getRecording() const
{
    return recording;
}

void Transcription::setRecording(Recording *rec)
{
    recording = rec;
}

QString Transcription::getFilename() const
{
    return filename;
}

int Transcription::getId() const
{
    return id;
}
