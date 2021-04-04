#include "m3u.h"

/*=============================================================================
 * process_list - empty contructor
 */
m3u::m3u()
{

}

/*=============================================================================
 * createChannelObjects - get channels from m3u file rows
 * This function reads all rows line by line,
 * and saves each channel to a channel list
 */
bool m3u::createChannelObjects(QStringList fileRows) {

    mChannels.clear();

    /* local variables */
    channel chan;
    QString row;
    QStringList parts;
    int sStart;
    int n;

    /* iterate through file rows */
    for (int i = 0; i < fileRows.count(); i++) {

        /* save row */
        row = fileRows[i];

        if (row.contains(" Oskar und die Tieferschatten")) {
            int u = i + 1 - 1;
            u++;
        }

        /* get additional atributes */
        if (row.contains("EXTM3U")) {

            /* not handeled yet */

        /* get extended informations */
        } else if (row.contains("EXTINF")) {

            /* split extended informations */
            parts = row.split(",");

            /* save channel name */
            chan.name = parts[parts.length()-1];

            /* get group title */
            sStart  = row.indexOf("group-title", 0);
            if (sStart != -1) {
                sStart  = row.indexOf("\"", sStart + 1);
                n       = row.indexOf("\"", sStart + 1) - sStart - 1;

                /* save group title */
                chan.groupName = row.mid(sStart + 1, n);

                if (!mChannelGroups.contains(chan.groupName)) {
                    mChannelGroups.append(chan.groupName);
                }
            }

            /* get tv guide id */
            sStart  = row.indexOf("tvg-id", 0);
            if (sStart != -1) {
                sStart  = row.indexOf("\"", sStart + 1);
                n       = row.indexOf("\"", sStart + 1) - sStart - 1;

                /* save tv guide id */
                chan.tvgID = row.mid(sStart + 1, n);
            }

            /* get tv guide name */
            sStart  = row.indexOf("tvg-name", 0);
            if (sStart != -1) {
                sStart  = row.indexOf("\"", sStart + 1);
                n       = row.indexOf("\"", sStart + 1) - sStart - 1;

                /* save tv guide name */
                chan.tvgName = row.mid(sStart + 1, n);
            }

            /* get tv guide logo */
            sStart  = row.indexOf("tvg-logo", 0);
            if (sStart != -1) {
                sStart  = row.indexOf("\"", sStart + 1);
                n       = row.indexOf("\"", sStart + 1) - sStart - 1;

                /* save tv guide logo */
                chan.tvgLogo = row.mid(sStart + 1, n);
            }

        /* get size */
        } else if (row.contains("EXTSIZE")) {

            /* not handeled yet */

        /* get background */
        } else if (row.contains("EXTBG")) {

            /* not handeled yet */

        /* get media path */
        } else if (row.contains("://")) {

            /* save channel url */
            chan.url = row;

            chan.channelNumber = i/2;

            /* append channel to channel list */
            mChannels.append(chan);

            /* reset channel */
            chan = channel();
        } else {

            /* nothing */

        }
    }

    return true;
}
