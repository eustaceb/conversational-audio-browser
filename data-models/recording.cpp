#include "recording.h"
#include "sndfile.hh"

#include <QDebug>

Recording::Recording(const QString &filename)
{
    this->filename = filename;
    originalFile = SndfileHandle(filename.toStdString());
}

Recording::~Recording()
{

}

int Recording::sliceOut(double from, double to, QString resultFile)
{
    const int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    const int MAX_BUFFER_SIZE = originalFile.samplerate() * originalFile.channels();

    SndfileHandle outFile(resultFile.toStdString(), SFM_WRITE, format, originalFile.channels(), originalFile.samplerate());
    if (!outFile) return -1;

    originalFile.seek(from * originalFile.samplerate(), SEEK_SET);

    int ms = (to - from) * 1000;
    double samplesPer10Ms = (originalFile.samplerate() / 100) * originalFile.channels();
    int framesTotal = samplesPer10Ms * (ms / 10);

    //qInfo() << "About to export" << resultFile << "length of " << ms << "ms or" << ms / 1000 << "s";
    //qInfo() << "Samples per 10ms" << samplesPer10Ms << "total frames" << framesTotal;

    short *buffer = new short[MAX_BUFFER_SIZE];

    int count = 0;
    while (count < framesTotal) {
        sf_count_t toWrite = ((count + MAX_BUFFER_SIZE) < framesTotal) ? MAX_BUFFER_SIZE : (framesTotal - count);
        //if (toWrite % 2 != 0) toWrite--;

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
