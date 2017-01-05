#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>

class Transcription;

#include "trees/selectiontreemodel.h"
#include "trees/filtertreemodel.h"

#include "transcription.h"

class Helpers
{
public:
    Helpers();

    static SelectionTreeModel* generateSelectionTree(Transcription *t);
    static FilterTreeModel* generateFilterTree(Transcription *t);

    static Transcription* parseTranscript(const QString &fileName);
};

#endif // HELPERS_H
