#ifndef HELPERS_H
#define HELPERS_H

#include <transcription.h>

class Helpers
{
public:
    Helpers();
    static Transcription parseTranscript(const QString &fileName);
};

#endif // HELPERS_H
