#include "recording.h"
#include "sndfile.hh"

#include <QDebug>
#include <cmath>

Recording::Recording(const QString &filename)
{
    this->filename = filename;
    originalFile = SndfileHandle(filename.toStdString());
}

Recording::~Recording()
{

}

int Recording::sliceOut(qreal from, qreal to, QString resultFile)
{
    const int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    const int MAX_BUFFER_SIZE = originalFile.samplerate() * originalFile.channels();

    SndfileHandle outFile(resultFile.toStdString(), SFM_WRITE, format, originalFile.channels(), originalFile.samplerate());
    if (!outFile) return -1;

    originalFile.seek(from * originalFile.samplerate(), SEEK_SET);

    int ms = (to - from) * 1000;
    qreal samplesPerMs = (originalFile.samplerate() / 1000) * originalFile.channels();
    // Slight data loss if sample rate not divisable by 1000, round up to prevent
    int framesTotal = ceil(samplesPerMs) * ms;

    short *buffer = new short[MAX_BUFFER_SIZE];

    int count = 0;
    while (count < framesTotal) {
        sf_count_t toWrite = ((count + MAX_BUFFER_SIZE) < framesTotal) ? MAX_BUFFER_SIZE : (framesTotal - count);

        originalFile.read(buffer, toWrite);
        outFile.write(buffer, toWrite);
        count += toWrite;
    }
    delete [] buffer;
    return 0;
}

QString Recording::getFilename() const
{
    return filename;
}
