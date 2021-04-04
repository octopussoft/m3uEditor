#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H
#include <QString>
#include <QStringList>
#include "channel.h"

class m3u
{
public:
    m3u();

    bool createChannelObjects(QStringList fileRows);


    QList<channel> mChannels;
    QStringList mChannelGroups;

    private:
};

#endif // PROCESS_LIST_H
