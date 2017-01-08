#ifndef RECORDING_H
#define RECORDING_H

#include <QString>

class Recording
{
public:
    Recording(const QString &filename);

    QString getFilename() const;
    void setFilename(const QString &value);

private:
    QString filename;
};

#endif // RECORDING_H
