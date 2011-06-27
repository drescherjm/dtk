/* dtkZipFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:09:22 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:10:42 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#include "dtkZipFile.h"

using namespace std;

class dtkZipFilePrivate
{
    friend class dtkZipFile;

private:
    dtkZipFile *q;
    dtkZip *zip;
    QString fileName;
    dtkZip::CaseSensitivity caseSensitivity;
    bool raw;
    qint64 writePos;

    ulong uncompressedSize;
    quint32 crc;
    bool internal;
    int zipError;

    inline void resetZipError() const {setZipError(UNZ_OK);}

    void setZipError(int zipError) const;

    inline dtkZipFilePrivate(dtkZipFile *q):
        q(q), zip(NULL), internal(true), zipError(UNZ_OK) {}

    inline dtkZipFilePrivate(dtkZipFile *q, const QString &zipName):
        q(q), internal(true), zipError(UNZ_OK)
        {
            zip=new dtkZip(zipName);
        }

    inline dtkZipFilePrivate(dtkZipFile *q, const QString &zipName, const QString &fileName,
                             dtkZip::CaseSensitivity cs):
        q(q), internal(true), zipError(UNZ_OK)
        {
            zip=new dtkZip(zipName);
            this->fileName=fileName;
            this->caseSensitivity=cs;
        }

    inline dtkZipFilePrivate(dtkZipFile *q, dtkZip *zip):
        q(q), zip(zip), internal(false), zipError(UNZ_OK) {}

    inline ~dtkZipFilePrivate()
        {
            if (internal)
                delete zip;
        }
};

dtkZipFile::dtkZipFile():
    p(new dtkZipFilePrivate(this))
{
}

dtkZipFile::dtkZipFile(QObject *parent):
    QIODevice(parent),
    p(new dtkZipFilePrivate(this))
{
}

dtkZipFile::dtkZipFile(const QString& zipName, QObject *parent):
    QIODevice(parent),
    p(new dtkZipFilePrivate(this, zipName))
{
}

dtkZipFile::dtkZipFile(const QString& zipName, const QString& fileName,
                       dtkZip::CaseSensitivity cs, QObject *parent):
    QIODevice(parent),
    p(new dtkZipFilePrivate(this, zipName, fileName, cs))
{
}

dtkZipFile::dtkZipFile(dtkZip *zip, QObject *parent):
    QIODevice(parent),
    p(new dtkZipFilePrivate(this, zip))
{
}

dtkZipFile::~dtkZipFile()
{
    if (isOpen())
        close();
    delete p;
}

QString dtkZipFile::getZipName() const
{
    return p->zip==NULL ? QString() : p->zip->getZipName();
}

QString dtkZipFile::getActualFileName()const
{
    p->setZipError(UNZ_OK);
    if (p->zip == NULL || (openMode() & WriteOnly))
        return QString();
    QString name=p->zip->getCurrentFileName();
    if(name.isNull())
        p->setZipError(p->zip->getZipError());
    return name;
}

void dtkZipFile::setZipName(const QString& zipName)
{
    if(isOpen()) {
        qWarning("dtkZipFile::setZipName(): file is already open - can not set ZIP name");
        return;
    }
    if(p->zip!=NULL && p->internal)
        delete p->zip;
    p->zip=new dtkZip(zipName);
    p->internal=true;
}

void dtkZipFile::setZip(dtkZip *zip)
{
    if(isOpen()) {
        qWarning("dtkZipFile::setZip(): file is already open - can not set ZIP");
        return;
    }
    if(p->zip!=NULL && p->internal)
        delete p->zip;
    p->zip=zip;
    p->fileName=QString();
    p->internal=false;
}

void dtkZipFile::setFileName(const QString& fileName, dtkZip::CaseSensitivity cs)
{
    if(p->zip==NULL) {
        qWarning("dtkZipFile::setFileName(): call setZipName() first");
        return;
    }
    if(!p->internal) {
        qWarning("dtkZipFile::setFileName(): should not be used when not using internal dtkZip");
        return;
    }
    if(isOpen()) {
        qWarning("dtkZipFile::setFileName(): can not set file name for already opened file");
        return;
    }
    p->fileName=fileName;
    p->caseSensitivity=cs;
}

void dtkZipFilePrivate::setZipError(int zipError) const
{
    dtkZipFilePrivate *fakeThis = const_cast<dtkZipFilePrivate*>(this); // non-const
    fakeThis->zipError=zipError;
    if(zipError==UNZ_OK)
        q->setErrorString(QString());
    else
        q->setErrorString(q->tr("ZIP/UNZIP API error %1").arg(zipError));
}

bool dtkZipFile::open(OpenMode mode)
{
    return open(mode, NULL);
}

bool dtkZipFile::open(OpenMode mode, int *method, int *level, bool raw, const char *password)
{
    p->resetZipError();
    if(isOpen()) {
        qWarning("dtkZipFile::open(): already opened");
        return false;
    }
    if(mode&Unbuffered) {
        qWarning("dtkZipFile::open(): Unbuffered mode is not supported");
        return false;
    }
    if((mode&ReadOnly)&&!(mode&WriteOnly)) {
        if(p->internal) {
            if(!p->zip->open(dtkZip::mdUnzip)) {
                p->setZipError(p->zip->getZipError());
                return false;
            }
            if(!p->zip->setCurrentFile(p->fileName, p->caseSensitivity)) {
                p->setZipError(p->zip->getZipError());
                p->zip->close();
                return false;
            }
        } else {
            if(p->zip==NULL) {
                qWarning("dtkZipFile::open(): zip is NULL");
                return false;
            }
            if(p->zip->getMode()!=dtkZip::mdUnzip) {
                qWarning("dtkZipFile::open(): file open mode %d incompatible with ZIP open mode %d",
                         (int)mode, (int)p->zip->getMode());
                return false;
            }
            if(!p->zip->hasCurrentFile()) {
                qWarning("dtkZipFile::open(): zip does not have current file");
                return false;
            }
        }
        p->setZipError(unzOpenCurrentFile3(p->zip->getUnzFile(), method, level, (int)raw, password));
        if(p->zipError==UNZ_OK) {
            setOpenMode(mode);
            p->raw=raw;
            return true;
        } else
            return false;
    }
    qWarning("dtkZipFile::open(): open mode %d not supported by this function", (int)mode);
    return false;
}

bool dtkZipFile::open(OpenMode mode, const dtkZipNewInfo& info,
                      const char *password, quint32 crc,
                      int method, int level, bool raw,
                      int windowBits, int memLevel, int strategy)
{
    zip_fileinfo info_z;
    p->resetZipError();
    if(isOpen()) {
        qWarning("dtkZipFile::open(): already opened");
        return false;
    }
    if((mode&WriteOnly)&&!(mode&ReadOnly)) {
        if(p->internal) {
            qWarning("dtkZipFile::open(): write mode is incompatible with internal dtkZip approach");
            return false;
        }
        if(p->zip==NULL) {
            qWarning("dtkZipFile::open(): zip is NULL");
            return false;
        }
        if(p->zip->getMode()!=dtkZip::mdCreate&&p->zip->getMode()!=dtkZip::mdAppend&&p->zip->getMode()!=dtkZip::mdAdd) {
            qWarning("dtkZipFile::open(): file open mode %d incompatible with ZIP open mode %d",
                     (int)mode, (int)p->zip->getMode());
            return false;
        }
        info_z.tmz_date.tm_year=info.dateTime.date().year();
        info_z.tmz_date.tm_mon=info.dateTime.date().month() - 1;
        info_z.tmz_date.tm_mday=info.dateTime.date().day();
        info_z.tmz_date.tm_hour=info.dateTime.time().hour();
        info_z.tmz_date.tm_min=info.dateTime.time().minute();
        info_z.tmz_date.tm_sec=info.dateTime.time().second();
        info_z.dosDate = 0;
        info_z.internal_fa=(uLong)info.internalAttr;
        info_z.external_fa=(uLong)info.externalAttr;
        p->setZipError(zipOpenNewFileInZip3(p->zip->getZipFile(),
                                            p->zip->getFileNameCodec()->fromUnicode(info.name).constData(), &info_z,
                                            info.extraLocal.constData(), info.extraLocal.length(),
                                            info.extraGlobal.constData(), info.extraGlobal.length(),
                                            p->zip->getCommentCodec()->fromUnicode(info.comment).constData(),
                                            method, level, (int)raw,
                                            windowBits, memLevel, strategy,
                                            password, (uLong)crc));
        if(p->zipError==UNZ_OK) {
            p->writePos=0;
            setOpenMode(mode);
            p->raw=raw;
            if(raw) {
                p->crc=crc;
                p->uncompressedSize=info.uncompressedSize;
            }
            return true;
        } else
            return false;
    }
    qWarning("dtkZipFile::open(): open mode %d not supported by this function", (int)mode);
    return false;
}

bool dtkZipFile::isSequential()const
{
    return true;
}

qint64 dtkZipFile::pos()const
{
    if(p->zip==NULL) {
        qWarning("dtkZipFile::pos(): call setZipName() or setZip() first");
        return -1;
    }
    if(!isOpen()) {
        qWarning("dtkZipFile::pos(): file is not open");
        return -1;
    }
    if(openMode()&ReadOnly)
        return unztell(p->zip->getUnzFile());
    else
        return p->writePos;
}

bool dtkZipFile::atEnd()const
{
    if(p->zip==NULL) {
        qWarning("dtkZipFile::atEnd(): call setZipName() or setZip() first");
        return false;
    }
    if(!isOpen()) {
        qWarning("dtkZipFile::atEnd(): file is not open");
        return false;
    }
    if(openMode()&ReadOnly)
        return unzeof(p->zip->getUnzFile())==1;
    else
        return true;
}

qint64 dtkZipFile::size()const
{
    if(!isOpen()) {
        qWarning("dtkZipFile::atEnd(): file is not open");
        return -1;
    }
    if(openMode()&ReadOnly)
        return p->raw?csize():usize();
    else
        return p->writePos;
}

qint64 dtkZipFile::csize()const
{
    unz_file_info info_z;
    p->setZipError(UNZ_OK);
    if(p->zip==NULL||p->zip->getMode()!=dtkZip::mdUnzip) return -1;
    p->setZipError(unzGetCurrentFileInfo(p->zip->getUnzFile(), &info_z, NULL, 0, NULL, 0, NULL, 0));
    if(p->zipError!=UNZ_OK)
        return -1;
    return info_z.compressed_size;
}

qint64 dtkZipFile::usize()const
{
    unz_file_info info_z;
    p->setZipError(UNZ_OK);
    if(p->zip==NULL||p->zip->getMode()!=dtkZip::mdUnzip) return -1;
    p->setZipError(unzGetCurrentFileInfo(p->zip->getUnzFile(), &info_z, NULL, 0, NULL, 0, NULL, 0));
    if(p->zipError!=UNZ_OK)
        return -1;
    return info_z.uncompressed_size;
}

bool dtkZipFile::getFileInfo(dtkZipFileInfo *info)
{
    if(p->zip==NULL||p->zip->getMode()!=dtkZip::mdUnzip) return false;
    p->zip->getCurrentFileInfo(info);
    p->setZipError(p->zip->getZipError());
    return p->zipError==UNZ_OK;
}

void dtkZipFile::close()
{
    p->resetZipError();
    if(p->zip==NULL||!p->zip->isOpen()) return;
    if(!isOpen()) {
        qWarning("dtkZipFile::close(): file isn't open");
        return;
    }
    if(openMode()&ReadOnly)
        p->setZipError(unzCloseCurrentFile(p->zip->getUnzFile()));
    else if(openMode()&WriteOnly)
        if(isRaw()) p->setZipError(zipCloseFileInZipRaw(p->zip->getZipFile(), p->uncompressedSize, p->crc));
        else p->setZipError(zipCloseFileInZip(p->zip->getZipFile()));
    else {
        qWarning("Wrong open mode: %d", (int)openMode());
        return;
    }
    if(p->zipError==UNZ_OK) setOpenMode(QIODevice::NotOpen);
    else return;
    if(p->internal) {
        p->zip->close();
        p->setZipError(p->zip->getZipError());
    }
}

qint64 dtkZipFile::readData(char *data, qint64 maxSize)
{
    p->setZipError(UNZ_OK);
    qint64 bytesRead=unzReadCurrentFile(p->zip->getUnzFile(), data, (unsigned)maxSize);
    if(bytesRead<0) p->setZipError((int)bytesRead);
    return bytesRead;
}

qint64 dtkZipFile::writeData(const char* data, qint64 maxSize)
{
    p->setZipError(ZIP_OK);
    p->setZipError(zipWriteInFileInZip(p->zip->getZipFile(), data, (uint)maxSize));
    if(p->zipError!=ZIP_OK) return -1;
    else {
        p->writePos+=maxSize;
        return maxSize;
    }
}

QString dtkZipFile::getFileName() const
{
    return p->fileName;
}

dtkZip::CaseSensitivity dtkZipFile::getCaseSensitivity() const
{
    return p->caseSensitivity;
}

bool dtkZipFile::isRaw() const
{
    return p->raw;
}

int dtkZipFile::getZipError() const
{
    return p->zipError;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

/*
  Copyright (C) 2005-2011 Sergey A. Tachenov
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at
  your option) any later version.
  
  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
  General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
  
  See COPYING file for the full LGPL text.
  
  Original ZIP package is copyrighted by Gilles Vollant, see
  quazip/(un)zip.h files for details, basically it's zlib license.
**/
