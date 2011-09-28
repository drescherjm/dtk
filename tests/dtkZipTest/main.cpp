/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 23 13:20:05 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 26 12:37:22 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 123
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkZip/dtkZipReader.h>
#include <dtkZip/dtkZipWriter.h>

#include <QtCore>
#include <QtDebug>

bool basicUnpack(const QString &archive_path)
{
    dtkZipReader zip(archive_path + "/test.zip", QIODevice::ReadOnly);

    QList<dtkZipReader::FileInfo> files = zip.fileInfoList();

    if(files.count() != 2)
        return false;

    dtkZipReader::FileInfo fi = files.at(0);

    if(!(fi.isValid()))
        return false;

    if(!(fi.filePath == QString("test/")))
        return false;

    if(!(uint(fi.isDir) == (uint)1))
        return false;

    if(!(uint(fi.isFile) == (uint)0))
        return false;

    if(!(uint(fi.isSymLink) == (uint)0))
        return false;

    if(!(fi.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner
                                            | QFile::ReadUser  | QFile::WriteUser  | QFile::ExeUser)))
        return false;

    if(!(fi.lastModified == QDateTime::fromString("2005.11.11 13:08:02", "yyyy.MM.dd HH:mm:ss")))
        return false;

    fi = files.at(1);

    if(!(fi.isValid()))
        return false;

    if(!(fi.filePath == QString("test/test.txt")))
        return false;

    if(!(uint(fi.isDir) == (uint)0))
        return false;

    if(!(uint(fi.isFile) == (uint)1))
        return false;

    if(!(uint(fi.isSymLink) == (uint)0))
        return false;

    if(!(fi.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner
                                            | QFile::ReadUser  | QFile::WriteUser)))
        return false;

    if(!(fi.lastModified == QDateTime::fromString("2005.11.11 13:08:02", "yyyy.MM.dd HH:mm:ss")))
        return false;

    if(!(zip.fileData("test/test.txt") == QByteArray("content\n")))
        return false;

    return true;
}

bool symlinks(const QString& archive_path)
{
    dtkZipReader zip(archive_path + "/symlink.zip", QIODevice::ReadOnly);

    QList<dtkZipReader::FileInfo> files = zip.fileInfoList();

    if(!(files.count() == 2))
        return false;

    dtkZipReader::FileInfo fi = files.at(0);

    if(!(fi.isValid()))
        return false;

    if(!(fi.filePath == QString("symlink")))
        return false;

    if(!(!fi.isDir))
        return false;

    if(!(!fi.isFile))
        return false;

    if(!(fi.isSymLink))
        return false;

    if(!(zip.fileData("symlink") == QByteArray("destination")))
        return false;

    fi = files.at(1);

    if(!(fi.isValid()))
        return false;

    if(!(fi.filePath == QString("destination")))
        return false;

    if(!(!fi.isDir))
        return false;

    if(!(fi.isFile))
        return false;

    if(!(!fi.isSymLink))
        return false;

    return true;
}

bool readTest(void)
{
    dtkZipReader zip("foobar.zip", QIODevice::ReadOnly);

    QList<dtkZipReader::FileInfo> files = zip.fileInfoList();
    
    if(!(files.count() == 0))
        return false;

    QByteArray b = zip.fileData("foobar");

    if(!(b.size() == 0))
        return false;

    return true;
}

bool createArchive(void)
{
    QBuffer buffer;

    QByteArray fileContents("simple file contents\nline2\n");

    dtkZipWriter zip(&buffer);
    zip.addFile("My Filename", fileContents);
    zip.close();

    QByteArray zipFile = buffer.buffer();

    QBuffer buffer2(&zipFile);

    dtkZipReader zip2(&buffer2);

    QList<dtkZipReader::FileInfo> files = zip2.fileInfoList();

    if(!(files.count() == 1))
        return false;

    dtkZipReader::FileInfo file = files.at(0);

    if(!(file.filePath == QString("My Filename")))
        return false;

    if(!(uint(file.isDir) == (uint)0))
        return false;

    if(!(uint(file.isFile) == (uint) 1))
        return false;

    if(!(uint(file.isSymLink) == (uint) 0))
        return false;

    if(!(file.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ReadUser | QFile::WriteUser)))
        return false;

    if(!(file.size == (long long)27))
        return false;

    if(!(zip2.fileData("My Filename") == fileContents))
        return false;

    return true;
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 0;

    QString archive_path = argv[1];

    if(!(basicUnpack(archive_path)))
        return 1;

    if(!(symlinks(archive_path)))
        return 1;

    if(!readTest())
        return 1;

    if(!createArchive())
        return 1;

    return 0;
}
