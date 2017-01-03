#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>

class Transcription;

#include "selection/selectiontreemodel.h"
#include "transcription.h"

class Helpers
{
public:
    Helpers();

    static SelectionTreeModel* generateSelectionTree(Transcription *t);
    static SelectionTreeModel* generateFilterTree(Transcription *t);

    static Transcription* parseTranscript(const QString &fileName);
};

#endif // HELPERS_H
