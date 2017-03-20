#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QMultiMap>
#include <QStandardItemModel>

class Transcription;

class Helpers
{
public:
    static Transcription* parseTranscript(QIODevice *source);
    static int exportStdItemModelToCsv(const QString &filename, QStandardItemModel *model, bool headers = 1);
};

#endif // HELPERS_H
