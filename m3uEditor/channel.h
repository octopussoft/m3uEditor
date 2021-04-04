#ifndef CHANNEL_H
#define CHANNEL_H
#include <QString>


class channel
{
public:
    channel();

    /* m3u channel member */
    uint channelNumber;
    QString name;
    QString url;
    QString lenth;

    QString tvgID;
    QString tvgName;
    QString tvgLogo;
    QString groupName;
};

#endif // CHANNEL_H
