/* dtkZipFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:06:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:09:16 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#ifndef DTK_ZIPFILE_H
#define DTK_ZIPFILE_H

#include <QIODevice>

#include "dtkZip.h"
#include "dtkZipExport.h"
#include "dtkZipUtils.h"
#include "dtkZipNewInfo.h"

class dtkZipFilePrivate;

class DTKZIP_EXPORT dtkZipFile: public QIODevice
{
    Q_OBJECT

        friend class dtkZipFilePrivate;

private:
    dtkZipFilePrivate *p;
    dtkZipFile(const dtkZipFile& that);
    dtkZipFile& operator=(const dtkZipFile& that);

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);

public:
    dtkZipFile();
    dtkZipFile(QObject *parent);
    dtkZipFile(const QString& zipName, QObject *parent =NULL);
    dtkZipFile(const QString& zipName, const QString& fileName, dtkZip::CaseSensitivity cs =dtkZip::csDefault, QObject *parent =NULL);
    dtkZipFile(dtkZip *zip, QObject *parent =NULL);
    virtual ~dtkZipFile();

    QString getZipName()const;

    dtkZip* getZip()const;

    QString getFileName() const;

    dtkZip::CaseSensitivity getCaseSensitivity() const;

    QString getActualFileName()const;

    void setZipName(const QString& zipName);

    bool isRaw() const;

    void setZip(dtkZip *zip);

    void setFileName(const QString& fileName, dtkZip::CaseSensitivity cs =dtkZip::csDefault);

    virtual bool open(OpenMode mode);

    inline bool open(OpenMode mode, const char *password)
    {
        return open(mode, NULL, NULL, false, password);
    }

    bool open(OpenMode mode, int *method, int *level, bool raw, const char *password =NULL);
    bool open(OpenMode mode, const dtkZipNewInfo& info,
              const char *password =NULL, quint32 crc =0,
              int method =Z_DEFLATED, int level =Z_DEFAULT_COMPRESSION, bool raw =false,
              int windowBits =-MAX_WBITS, int memLevel =DEF_MEM_LEVEL, int strategy =Z_DEFAULT_STRATEGY);

    virtual bool isSequential()const;
    virtual qint64 pos()const;
    virtual bool atEnd()const;
    virtual qint64 size()const;

    qint64 csize()const;
    qint64 usize()const;

    bool getFileInfo(dtkZipFileInfo *info);

    virtual void close();

    int getZipError() const;
};

#endif

// /////////////////////////////////////////////////////////////////
// Credits
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
