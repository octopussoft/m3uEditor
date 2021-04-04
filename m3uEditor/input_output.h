#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include "m3u.h"

class input_output
{
public:
    input_output();

    bool read_m3u(QString path);
    bool write_m3u(QString path, QList<channel> playlist);
    QStringList getfileRows();

private:
    QStringList mFileRows;
};

#endif // INPUT_OUTPUT_H
