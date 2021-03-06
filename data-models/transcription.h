#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

#include <QList>

#include "selectable.h"
#include "filterable.h"

class Topic;
class Speaker;
class Recording;
class Turn;
class Section;

class Transcription : public Selectable, public Filterable
{
public:
    Transcription(const QString &filepath);
    virtual ~Transcription();

    void addTopic(Topic *t);
    void addSpeaker(Speaker *s);
    QList<Topic *> getTopics() const;
    QList<Speaker *> getSpeakers() const;

    QList<Turn *> getTurnList(bool selected = false) const;
    QList<Section *> getSectionList(bool selected = false) const;

    QList<QVariant> composeTreePayload() const Q_DECL_OVERRIDE;
    QString getFilepath() const;

    Recording *getRecording() const;
    void setRecording(Recording *rec);

    QString getFilename() const;
    QString getTitle() const;

    int getId() const;

private:
    static int idCounter;
    int id;
    QString filepath, filename, title;
    Recording *recording;
    QList <Topic*> topics;
    QList <Speaker*> speakers;
};

#endif // TRANSCRIPTION_H
