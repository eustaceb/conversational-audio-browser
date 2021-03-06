#ifndef RECORDING_H
#define RECORDING_H

#include "sndfile.hh"
#include <QString>

class Recording
{
public:
    Recording(const QString &filename);
    ~Recording();

    int sliceOut(qreal from, qreal to, QString resultFile);

    QString getFilename() const;

private:
    QString filename;

    SndfileHandle originalFile;
};

#endif // RECORDING_H
