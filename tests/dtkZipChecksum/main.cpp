/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:41:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:46:33 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QFile>
#include <QTextStream>

#include <stdlib.h>
#include <stdio.h>

#include <dtkZip/dtkZipUtils.h>

bool isSmallFile(const QFile &file)
{
    return file.size() < 1*1024*1024; // < 1 MB
}

int main(int argc, char* argv[])
{
    QTextStream console(stdout);

    if(argc != 2)
    {
        console << "usage: checksum filepath\n";
        return -1;
    }

    QFile file(argv[1]);
    if( !file.open(QFile::ReadOnly) )
    {
        console << "Coulden't open file " << argv[1] << '\n';
        return -2;
    }

    quint32 resoult;

    dtkChecksum32 *checksum = new dtkCrc32();
	
    if(isSmallFile(file))
    {
        resoult = checksum->calculate(file.readAll());
    }
    else
    {
        const quint64 bufSize = 500*1024;

        while(!file.atEnd())
        {
            checksum->update(file.read(bufSize));
        }
        resoult = checksum->value();
    }
	
    console << "checksum: " << hex << resoult << '\n';

    return 0;
}
