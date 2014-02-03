/* dtkCompareDoubleTest.cpp ---
 *
 * Author: Babette Lekouta
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 14:09:48 2012 (+0200)
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkZipTest.h"

#include <dtkZip/dtkZipReader.h>
#include <dtkZip/dtkZipWriter.h>

#include <QtCore>
#include <QtDebug>

#include <dtkConfig.h>

// /////////////////////////////////////////////////////////////////
// dtkZipTestObject
// /////////////////////////////////////////////////////////////////

class dtkZipTestObjectPrivate
{
public:
    QString archive_path;

public:
    QList<dtkZipReader::FileInfo> files;

public:
    dtkZipReader::FileInfo fi ;
    dtkZipReader::FileInfo file;

};

dtkZipTestObject::dtkZipTestObject(void)
{
    d = new dtkZipTestObjectPrivate;
    d->archive_path  = DTK_SOURCE_PATH;
    d->archive_path += "/tests/dtkZip";
}

dtkZipTestObject::~dtkZipTestObject(void)
{

}

void dtkZipTestObject::initTestCase(void)
{

}

void dtkZipTestObject::init(void)
{

}

void dtkZipTestObject::cleanup(void)
{

}

void dtkZipTestObject::cleanupTestCase(void)
{
    if (d)
        delete d;
}

void dtkZipTestObject::basicUnpack(void)
{
    dtkZipReader zip(d->archive_path + "/test.zip", QIODevice::ReadOnly);

    d-> files = zip.fileInfoList();
    QVERIFY(d->files.count() == 2);

    d->fi = d->files.at(0);
    QVERIFY(d->fi.isValid()) ;
    QVERIFY(d->fi.filePath == QString("test/")) ;
    QVERIFY(uint(d->fi.isDir == (uint)1));
    QVERIFY((uint(d->fi.isFile) == (uint)0));
    QVERIFY((uint(d->fi.isSymLink) == (uint)0));
    QVERIFY(d->fi.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner| QFile::ReadUser  | QFile::WriteUser  | QFile::ExeUser));
    QVERIFY(d->fi.lastModified == QDateTime::fromString("2005.11.11 13:08:02", "yyyy.MM.dd HH:mm:ss"));

    d->fi = d->files.at(1);
    QVERIFY(d->fi.isValid());
    QVERIFY(d->fi.filePath == QString("test/test.txt"));
    QVERIFY((uint(d->fi.isDir) == (uint)0));
    QVERIFY(uint(d->fi.isFile) == (uint)1);
    QVERIFY((uint(d->fi.isSymLink) == (uint)0));
    QVERIFY(d->fi.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner| QFile::ReadUser  | QFile::WriteUser));
    QVERIFY(d->fi.lastModified == QDateTime::fromString("2005.11.11 13:08:02", "yyyy.MM.dd HH:mm:ss"));
    QVERIFY(zip.fileData("test/test.txt") == QByteArray("content\n"));

}

void dtkZipTestObject::symlinks(void)
{
    dtkZipReader zip(d->archive_path + "/symlink.zip", QIODevice::ReadOnly);

    d->files = zip.fileInfoList();
    QVERIFY(d->files.count() == 2);

    d->fi = d->files.at(0);
    QVERIFY(d->fi.isValid());
    QVERIFY(d->fi.filePath == QString("symlink"));
    QVERIFY(!d->fi.isDir);
    QVERIFY(!d->fi.isFile);
    QVERIFY(d->fi.isSymLink);
    QVERIFY(zip.fileData("symlink") == QByteArray("destination"));

    d->fi = d->files.at(1);
    QVERIFY(d->fi.isValid());
    QVERIFY(zip.fileData("symlink") == QByteArray("destination"));
    QVERIFY(!d->fi.isDir);
    QVERIFY(d->fi.isFile);
    QVERIFY(!d->fi.isSymLink);

}

void dtkZipTestObject::readTest(void)
{
    dtkZipReader zip("foobar.zip", QIODevice::ReadOnly);
    QVERIFY((d->files.count() != 0));

    QByteArray b = zip.fileData("foobar");
    QVERIFY((b.size() == 0));
}

void dtkZipTestObject::createArchive(void)
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
    QVERIFY((files.count() == 1));

    d->file = d->files.at(0);
    QVERIFY(!(d->file.filePath == QString("My Filename")));
    QVERIFY(uint(d->file.isDir) == (uint)0);
    QVERIFY(!(uint(d->file.isFile) == (uint) 1));
    QVERIFY(!(uint(d->file.isSymLink) == (uint) 0));
    QVERIFY(!(d->file.permissions == QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ReadUser | QFile::WriteUser)));
    QVERIFY(!(d->file.size == (long long)27));
    QVERIFY((zip2.fileData("My Filename") == fileContents));
}

DTKTEST_NOGUI_MAIN(dtkZipTest,dtkZipTestObject)
