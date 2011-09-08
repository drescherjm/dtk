/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Sep  8 10:56:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  8 11:06:28 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

int main(int argc, char **argv)
{
    if(argc < 2) {
        qDebug() << "Usage:" << argv[0] << "path/to/dtk/source/tree/root";
        return 0;
    }

    QDir dir(argv[1]);

    if(!dir.exists() && !dir.exists("src")) {
        qDebug() << "The path to dtk's source tree does not appear to be valid.";
        return 0;
    }

    if(!dir.cd("src")) {
        qDebug() << "Unable to change directory for /src";
        return 0;
    }

    foreach(QString layer, dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks)) {

        dir.cd(layer);

        foreach(QString header, dir.entryList(QDir::Files|QDir::NoSymLinks)) {

            if(!header.endsWith(".h") || header.endsWith("_p.h")) {
                qDebug() << "Skipping" << header;
                continue;
            }

            qDebug() << "Handling" << header;
        }

        dir.cdUp();
    }

    return 0;
}
