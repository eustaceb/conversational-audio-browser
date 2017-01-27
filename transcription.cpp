#include "data-models/transcription.h"
#include "data-models/topic.h"
#include "data-models/speaker.h"
#include "data-models/recording.h"
#include "data-models/turn.h"

#include "helpers.h"

int Transcription::idCounter = 0;

Transcription::Transcription(const QString &filepath)
    : filepath(filepath), recording(0)
{
    this->id = idCounter++;
    QStringList splitFilepath = filepath.split("/");
    this->filename = splitFilepath.at(splitFilepath.length() - 1);
    this->title = this->filename.split(".").at(0);
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
    payload.append(QString::number(topics.length()) + " topics, " + QString::number(speakers.length()) + " speakers");
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
    delete recording;
    recording = rec;
}

QString Transcription::getFilename() const
{
    return filename;
}

QString Transcription::getTitle() const
{
    return title;
}

int Transcription::getId() const
{
    return id;
}
