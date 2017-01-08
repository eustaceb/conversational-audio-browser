#include "recording.h"

Recording::Recording(const QString &filename)
{
    this->filename = filename;
}

QString Recording::getFilename() const
{
    return filename;
}

void Recording::setFilename(const QString &value)
{
    filename = value;
}
