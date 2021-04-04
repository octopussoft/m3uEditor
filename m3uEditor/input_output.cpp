#include "input_output.h"

input_output::input_output()
{

}

bool input_output::read_m3u(QString path){

    // clear old list
    mFileRows.clear();

    /* set file */
    QFile file(path);

   /* open file */
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        /* open filestream */
        QTextStream input(&file);


        while(!input.atEnd()) {
            mFileRows.append(input.readLine());
        }
    } else {
        file.close();
        return false;
    }

    file.close();
    return true;
}

bool input_output::write_m3u(QString path, QList<channel> playlist){

    /* set file */
    QFile file(path);

   /* open file */
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        int counter = 0u;

        /* open filestream */
        QTextStream output(&file);

        output << "#EXTM3U\n";

        /* write channels */
        foreach (channel chan,  playlist) {

            /* write channel information */
            output << "#EXTINF:-1 tvg-id=\"" + chan.tvgID + "\" tvg-name=\"" + chan.name  + "\" tvg-logo=\"" + chan.tvgLogo + "\" group-title=\"" + chan.groupName + "\"," + chan.name + "\n";

            /* write channel url */
            if (counter != playlist.count() - 1) {
                output << chan.url + "\n";
            } else {
                output << chan.url;
            }

            counter++;
        }
    } else {
        file.close();
        return false;
    }

    file.close();
    return true;
}

QStringList input_output::getfileRows() {

    return mFileRows;
}
