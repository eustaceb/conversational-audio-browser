#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>

class Transcription;

class Helpers
{
public:
    Helpers();

    static Transcription* parseTranscript(const QString &filename);
};

#endif // HELPERS_H
