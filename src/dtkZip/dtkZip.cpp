/* dtkZip.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:03:46 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:05:31 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#include <QFile>

#include "dtkZip.h"

class dtkZipPrivate
{
    friend class dtkZip;

private:
    QTextCodec *fileNameCodec, *commentCodec;
    QString zipName;
    QIODevice *ioDevice;
    QString comment;
    dtkZip::Mode mode;

    union {
        unzFile unzFile_f;
        zipFile zipFile_f;
    };

    bool hasCurrentFile_f;
    int zipError;

    inline dtkZipPrivate():
        fileNameCodec(QTextCodec::codecForLocale()),
        commentCodec(QTextCodec::codecForLocale()),
        ioDevice(NULL),
        mode(dtkZip::mdNotOpen),
        hasCurrentFile_f(false),
        zipError(UNZ_OK) {}

    inline dtkZipPrivate(const QString &zipName):
        fileNameCodec(QTextCodec::codecForLocale()),
        commentCodec(QTextCodec::codecForLocale()),
        zipName(zipName),
        ioDevice(NULL),
        mode(dtkZip::mdNotOpen),
        hasCurrentFile_f(false),
        zipError(UNZ_OK) {}

    inline dtkZipPrivate(QIODevice *ioDevice):
        fileNameCodec(QTextCodec::codecForLocale()),
        commentCodec(QTextCodec::codecForLocale()),
        ioDevice(ioDevice),
        mode(dtkZip::mdNotOpen),
        hasCurrentFile_f(false),
        zipError(UNZ_OK) {}
};

dtkZip::dtkZip():
    p(new dtkZipPrivate())
{
}

dtkZip::dtkZip(const QString& zipName):
    p(new dtkZipPrivate(zipName))
{
}

dtkZip::dtkZip(QIODevice *ioDevice):
    p(new dtkZipPrivate(ioDevice))
{
}

dtkZip::~dtkZip()
{
    if(isOpen())
        close();
    delete p;
}

bool dtkZip::open(Mode mode, zlib_filefunc_def* ioApi)
{
    p->zipError=UNZ_OK;
    if(isOpen()) {
        qWarning("dtkZip::open(): ZIP already opened");
        return false;
    }
    QIODevice *ioDevice = p->ioDevice;
    if (ioDevice == NULL) {
        if (p->zipName.isEmpty()) {
            qWarning("dtkZip::open(): set either ZIP file name or IO device first");
            return false;
        } else {
            ioDevice = new QFile(p->zipName);
        }
    }
    switch(mode) {
    case mdUnzip:
        p->unzFile_f=unzOpen2(ioDevice, ioApi);
        if(p->unzFile_f!=NULL) {
            p->mode=mode;
            p->ioDevice = ioDevice;
            return true;
        } else {
            p->zipError=UNZ_OPENERROR;
            if (!p->zipName.isEmpty())
                delete ioDevice;
            return false;
        }
    case mdCreate:
    case mdAppend:
    case mdAdd:
        p->zipFile_f=zipOpen2(ioDevice,
                              mode==mdCreate?APPEND_STATUS_CREATE:
                              mode==mdAppend?APPEND_STATUS_CREATEAFTER:
                              APPEND_STATUS_ADDINZIP,
                              NULL,
                              ioApi);
        if(p->zipFile_f!=NULL) {
            p->mode=mode;
            p->ioDevice = ioDevice;
            return true;
        } else {
            p->zipError=UNZ_OPENERROR;
            if (!p->zipName.isEmpty())
                delete ioDevice;
            return false;
        }
    default:
        qWarning("dtkZip::open(): unknown mode: %d", (int)mode);
        if (!p->zipName.isEmpty())
            delete ioDevice;
        return false;
        break;
    }
}

void dtkZip::close()
{
    p->zipError=UNZ_OK;
    switch(p->mode) {
    case mdNotOpen:
        qWarning("dtkZip::close(): ZIP is not open");
        return;
    case mdUnzip:
        p->zipError=unzClose(p->unzFile_f);
        break;
    case mdCreate:
    case mdAppend:
    case mdAdd:
        p->zipError=zipClose(p->zipFile_f, p->commentCodec->fromUnicode(p->comment).constData());
        break;
    default:
        qWarning("dtkZip::close(): unknown mode: %d", (int)p->mode);
        return;
    }

    if (!p->zipName.isEmpty())
        delete p->ioDevice;
    if(p->zipError==UNZ_OK)
        p->mode=mdNotOpen;
}

void dtkZip::setZipName(const QString& zipName)
{
    if(isOpen()) {
        qWarning("dtkZip::setZipName(): ZIP is already open!");
        return;
    }
    p->zipName=zipName;
    p->ioDevice = NULL;
}

void dtkZip::setIoDevice(QIODevice *ioDevice)
{
    if(isOpen()) {
        qWarning("dtkZip::setIoDevice(): ZIP is already open!");
        return;
    }
    p->ioDevice = ioDevice;
    p->zipName = QString();
}

int dtkZip::getEntriesCount()const
{
    dtkZip *fakeThis=(dtkZip*)this;
    fakeThis->p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::getEntriesCount(): ZIP is not open in mdUnzip mode");
        return -1;
    }
    unz_global_info globalInfo;
    if((fakeThis->p->zipError=unzGetGlobalInfo(p->unzFile_f, &globalInfo))!=UNZ_OK)
        return p->zipError;
    return (int)globalInfo.number_entry;
}

QString dtkZip::getComment()const
{
    dtkZip *fakeThis=(dtkZip*)this;
    fakeThis->p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::getComment(): ZIP is not open in mdUnzip mode");
        return QString();
    }
    unz_global_info globalInfo;
    QByteArray comment;
    if((fakeThis->p->zipError=unzGetGlobalInfo(p->unzFile_f, &globalInfo))!=UNZ_OK)
        return QString();
    comment.resize(globalInfo.size_comment);
    if((fakeThis->p->zipError=unzGetGlobalComment(p->unzFile_f, comment.data(), comment.size())) < 0)
        return QString();
    fakeThis->p->zipError = UNZ_OK;
    return p->commentCodec->toUnicode(comment);
}

bool dtkZip::setCurrentFile(const QString& fileName, CaseSensitivity cs)
{
    p->zipError=UNZ_OK;

    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::setCurrentFile(): ZIP is not open in mdUnzip mode");
        return false;
    }

    if(fileName.isEmpty()) {
        p->hasCurrentFile_f=false;
        return true;
    }

    if(p->unzFile_f==NULL) {
        p->zipError=UNZ_PARAMERROR;
        return false;
    }
    if(fileName.length()>MAX_FILE_NAME_LENGTH) {
        p->zipError=UNZ_PARAMERROR;
        return false;
    }
    bool sens;
    if(cs==csDefault) {
#ifdef Q_WS_WIN
        sens=false;
#else
        sens=true;
#endif
    } else sens=cs==csSensitive;
    QString lower, current;
    if(!sens) lower=fileName.toLower();
    p->hasCurrentFile_f=false;
    for(bool more=goToFirstFile(); more; more=goToNextFile()) {
        current=getCurrentFileName();
        if(current.isEmpty()) return false;
        if(sens) {
            if(current==fileName) break;
        } else {
            if(current.toLower()==lower) break;
        }
    }
    return p->hasCurrentFile_f;
}

bool dtkZip::goToFirstFile()
{
    p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::goToFirstFile(): ZIP is not open in mdUnzip mode");
        return false;
    }
    p->zipError=unzGoToFirstFile(p->unzFile_f);
    p->hasCurrentFile_f=p->zipError==UNZ_OK;
    return p->hasCurrentFile_f;
}

bool dtkZip::goToNextFile()
{
    p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::goToFirstFile(): ZIP is not open in mdUnzip mode");
        return false;
    }
    p->zipError=unzGoToNextFile(p->unzFile_f);
    p->hasCurrentFile_f=p->zipError==UNZ_OK;
    if(p->zipError==UNZ_END_OF_LIST_OF_FILE)
        p->zipError=UNZ_OK;
    return p->hasCurrentFile_f;
}

bool dtkZip::getCurrentFileInfo(dtkZipFileInfo *info)const
{
    dtkZip *fakeThis=(dtkZip*)this; // non-const
    fakeThis->p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::getCurrentFileInfo(): ZIP is not open in mdUnzip mode");
        return false;
    }
    unz_file_info info_z;
    QByteArray fileName;
    QByteArray extra;
    QByteArray comment;
    if(info==NULL) return false;
    if(!isOpen()||!hasCurrentFile()) return false;
    if((fakeThis->p->zipError=unzGetCurrentFileInfo(p->unzFile_f, &info_z, NULL, 0, NULL, 0, NULL, 0))!=UNZ_OK)
        return false;
    fileName.resize(info_z.size_filename);
    extra.resize(info_z.size_file_extra);
    comment.resize(info_z.size_file_comment);
    if((fakeThis->p->zipError=unzGetCurrentFileInfo(p->unzFile_f, NULL,
                                                    fileName.data(), fileName.size(),
                                                    extra.data(), extra.size(),
                                                    comment.data(), comment.size()))!=UNZ_OK)
        return false;
    info->versionCreated=info_z.version;
    info->versionNeeded=info_z.version_needed;
    info->flags=info_z.flag;
    info->method=info_z.compression_method;
    info->crc=info_z.crc;
    info->compressedSize=info_z.compressed_size;
    info->uncompressedSize=info_z.uncompressed_size;
    info->diskNumberStart=info_z.disk_num_start;
    info->internalAttr=info_z.internal_fa;
    info->externalAttr=info_z.external_fa;
    info->name=p->fileNameCodec->toUnicode(fileName);
    info->comment=p->commentCodec->toUnicode(comment);
    info->extra=extra;
    info->dateTime=QDateTime(
        QDate(info_z.tmu_date.tm_year, info_z.tmu_date.tm_mon+1, info_z.tmu_date.tm_mday),
        QTime(info_z.tmu_date.tm_hour, info_z.tmu_date.tm_min, info_z.tmu_date.tm_sec));
    return true;
}

QString dtkZip::getCurrentFileName()const
{
    dtkZip *fakeThis=(dtkZip*)this;
    fakeThis->p->zipError=UNZ_OK;
    if(p->mode!=mdUnzip) {
        qWarning("dtkZip::getCurrentFileName(): ZIP is not open in mdUnzip mode");
        return QString();
    }
    if(!isOpen()||!hasCurrentFile()) return QString();
    QByteArray fileName(MAX_FILE_NAME_LENGTH, 0);
    if((fakeThis->p->zipError=unzGetCurrentFileInfo(p->unzFile_f, NULL, fileName.data(), fileName.size(),
                                                    NULL, 0, NULL, 0))!=UNZ_OK)
        return QString();
    return p->fileNameCodec->toUnicode(fileName.constData());
}

void dtkZip::setFileNameCodec(QTextCodec *fileNameCodec)
{
    p->fileNameCodec=fileNameCodec;
}

void dtkZip::setFileNameCodec(const char *fileNameCodecName)
{
    p->fileNameCodec=QTextCodec::codecForName(fileNameCodecName);
}

QTextCodec *dtkZip::getFileNameCodec()const
{
    return p->fileNameCodec;
}

void dtkZip::setCommentCodec(QTextCodec *commentCodec)
{
    p->commentCodec=commentCodec;
}

void dtkZip::setCommentCodec(const char *commentCodecName)
{
    p->commentCodec=QTextCodec::codecForName(commentCodecName);
}

QTextCodec *dtkZip::getCommentCodec()const
{
    return p->commentCodec;
}

QString dtkZip::getZipName() const
{
    return p->zipName;
}

QIODevice *dtkZip::getIoDevice() const
{
    if (!p->zipName.isEmpty()) // opened by name, using an internal QIODevice
        return NULL;
    return p->ioDevice;
}

dtkZip::Mode dtkZip::getMode()const
{
    return p->mode;
}

bool dtkZip::isOpen()const
{
    return p->mode!=mdNotOpen;
}

int dtkZip::getZipError() const
{
    return p->zipError;
}

void dtkZip::setComment(const QString& comment)
{
    p->comment=comment;
}

bool dtkZip::hasCurrentFile()const
{
    return p->hasCurrentFile_f;
}

unzFile dtkZip::getUnzFile()
{
    return p->unzFile_f;
}

zipFile dtkZip::getZipFile()
{
    return p->zipFile_f;
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
