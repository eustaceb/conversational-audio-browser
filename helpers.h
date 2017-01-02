#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>

#include "transcription.h"
#include "selection/selectiontreemodel.h"

class Helpers
{
public:
    Helpers();
    static SelectionTreeModel* generateSelectionTree(Transcription *t);
    static Transcription* parseTranscript(const QString &fileName);
};

#endif // HELPERS_H
