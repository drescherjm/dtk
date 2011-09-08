/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Sep  8 10:56:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  8 13:06:59 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 86
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
    QDir inc(argv[1]);

    if(!dir.exists() && !dir.exists("src")) {
        qDebug() << "The path to dtk's source tree does not appear to be valid.";
        return 0;
    }

    if(!dir.cd("src")) {
        qDebug() << "Unable to change directory for /src.";
        return 0;
    }

    if(!inc.exists("include"))
        inc.mkdir("include");

    inc.cd("include");

    foreach(QString layer, dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks)) {

        dir.cd(layer);

        QStringList s_headers;

        foreach(QString s_header, dir.entryList(QDir::Files|QDir::NoSymLinks)) {

            if(!s_header.endsWith(".h") || s_header.endsWith("_p.h"))
                continue;

            s_headers << s_header;

            QString t_header(s_header); t_header.remove(".h");

            QFile header(dir.absoluteFilePath(t_header));
                
            if(!header.open(QFile::WriteOnly|QFile::Truncate)) {
                qDebug() << "Unable to create" << dir.absoluteFilePath(t_header);
                continue;
            }
            
            QTextStream out(&header);
            out << "#include \"" << s_header << "\"";
            
            header.close();
        }

        QString t_header(layer);
        
        QFile header(inc.absoluteFilePath(t_header));
        
        if(!header.open(QIODevice::WriteOnly)) {
            qDebug() << "Unable to create" << inc.absoluteFilePath(t_header);
            continue;
        }
        
        QTextStream out(&header);

        foreach(QString s_header, s_headers)
            out << "#include \"../src/" << layer << "/" << s_header << "\"\n";
        
        header.close();

        dir.cdUp();
    }

    return 0;
}
