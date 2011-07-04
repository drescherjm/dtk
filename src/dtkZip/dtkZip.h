/* dtkZip.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 14:59:07 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:03:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#ifndef DTK_ZIP_H
#define DTK_ZIP_H

#include "dtkZipUtils.h"
#include "dtkZipFileInfo.h"

#include <QtCore>

#ifndef UNZ_OPENERROR
#define UNZ_OPENERROR -1000
#endif

class dtkZipPrivate;

class DTKZIP_EXPORT dtkZip
{
    friend class dtkZipPrivate;

public:
    enum Constants {
        MAX_FILE_NAME_LENGTH=256
    };

    enum Mode {
        mdNotOpen,
        mdUnzip,
        mdCreate,
        mdAppend,
        mdAdd
    };

    enum CaseSensitivity {
        csDefault=0,
        csSensitive=1,
        csInsensitive=2
    };

private:
    dtkZipPrivate *p;

private:
    dtkZip(const dtkZip& that);
    dtkZip& operator=(const dtkZip& that);

public:
     dtkZip(void);
     dtkZip(const QString& zipName);
     dtkZip(QIODevice *ioDevice);
    ~dtkZip(void);

    bool open(Mode mode, zlib_filefunc_def *ioApi =NULL);
    void close();

    void setFileNameCodec(QTextCodec *fileNameCodec);
    void setFileNameCodec(const char *fileNameCodecName);

    QTextCodec* getFileNameCodec() const;

    void setCommentCodec(QTextCodec *commentCodec);
    void setCommentCodec(const char *commentCodecName);

    QTextCodec* getCommentCodec() const;

    QString getZipName() const;

    void setZipName(const QString& zipName);

    QIODevice *getIoDevice() const;

    void setIoDevice(QIODevice *ioDevice);

    Mode getMode() const;

    bool isOpen() const;

    int getZipError() const;
    int getEntriesCount() const;

    QString getComment() const;

    void setComment(const QString& comment);

    bool goToFirstFile();
    bool goToNextFile();

    bool setCurrentFile(const QString& fileName, CaseSensitivity cs =csDefault);
    bool hasCurrentFile() const;
    bool getCurrentFileInfo(dtkZipFileInfo* info)const;

    QString getCurrentFileName()const;

    unzFile getUnzFile();
    zipFile getZipFile();
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
