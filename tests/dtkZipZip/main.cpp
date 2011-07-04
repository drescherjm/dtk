/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:31:48 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:34:57 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QDir>
#include <QFile>

#include <dtkZip/dtkZip.h>
#include <dtkZip/dtkZipFile.h>

bool zip(void)
{
    QFile zipFile("test.zip");

    dtkZip zip(&zipFile);

    if(!zip.open(dtkZip::mdCreate)) {
        qWarning("testCreate(): zip.open(): %d", zip.getZipError());
        return false;
    }
    zip.setComment("Test comment");

    QFileInfoList files=QDir().entryInfoList();
    QFile inFile;

    dtkZipFile outFile(&zip);

    char c;

    foreach(QFileInfo file, files) {

        if(!file.isFile()||file.fileName()=="test.zip")
            continue;

        inFile.setFileName(file.fileName());

        if(!inFile.open(QIODevice::ReadOnly)) {
            qWarning("testCreate(): inFile.open(): %s", inFile.errorString().toLocal8Bit().constData());
            return false;
        }

        if(!outFile.open(QIODevice::WriteOnly, dtkZipNewInfo(inFile.fileName(), inFile.fileName()))) {
            qWarning("testCreate(): outFile.open(): %d", outFile.getZipError());
            return false;
        }

        qint64 len = file.size();
        qint64 pos = 0;

        while (inFile.getChar(&c)&&outFile.putChar(c)) {
            char buf[4096];
            qint64 l = inFile.read(buf, 4096);

            if (l < 0) {
                qWarning("read(): %s", inFile.errorString().toUtf8().constData());
                break;
            }

            if (l == 0)
                break;

            if (outFile.write(buf, l) != l) {
                qWarning("write(): %d", outFile.getZipError());
                break;
            }

            pos += l;

            if (pos % 1048576 == 0)
                qDebug("%.1f", (float) pos / len * 100.0f);
        }

        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.putChar(): %d", outFile.getZipError());
            return false;
        }

        outFile.close();

        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.close(): %d", outFile.getZipError());
            return false;
        }

        inFile.close();
    }

    zip.close();

    if(zip.getZipError()!=0) {
        qWarning("testCreate(): zip.close(): %d", zip.getZipError());
        return false;
    }

    return true;
}

int main(void)
{
    if(!zip())
        return 1;
    
    return 0;
}
