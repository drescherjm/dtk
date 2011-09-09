/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Sep  8 10:56:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  8 16:51:39 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 113
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
        qDebug() << "Usage:" << argv[0] << "path/to/dtk/install/path";
        return 0;
    }

    QDir dir(argv[1]);

    if(!dir.exists() && !dir.exists("includes")) {
        qDebug() << "The path to dtk's install tree does not appear to be valid.";
        return 0;
    }

    if(!dir.cd("includes")) {
        qDebug() << "Unable to change directory for /includes.";
        return 0;
    }

    foreach(QString header, dir.entryList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks)) {

        QFile file(dir.absoluteFilePath(header));
                
        if(!file.open(QFile::ReadOnly|QFile::Truncate)) {
            qDebug() << "Unable to create" << dir.absoluteFilePath(header);
            continue;
        }
            
        QTextStream in(&file);

        QString contents = in.readAll();
        contents.replace("../src", "../include");
        
        file.close();
        
        if(!file.open(QFile::WriteOnly|QFile::Truncate)) {
            qDebug() << "Unable to create" << dir.absoluteFilePath(header);
            continue;
        }
        
        QTextStream out(&file);
        out << contents;
        
        file.close();
    }

    return 0;
}
