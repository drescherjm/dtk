/* dtkZipReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 23 11:25:31 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 23 12:49:23 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#ifndef DTKZIPREADER_H
#define DTKZIPREADER_H

#include "dtkZipExport.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QString>

class dtkZipReaderPrivate;

class DTKZIP_EXPORT dtkZipReader
{
public:
    enum Status {
        NoError,
        FileReadError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

public:
    struct DTKZIP_EXPORT FileInfo {

         FileInfo(void);
         FileInfo(const FileInfo& other);
        ~FileInfo(void);

        FileInfo &operator=(const FileInfo& other);

        bool isValid() const;

        QString filePath;

        uint isDir : 1;
        uint isFile : 1;
        uint isSymLink : 1;

        QFile::Permissions permissions;

        uint crc32;
        qint64 size;
        QDateTime lastModified;
        void *d;
    };

public:
             dtkZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly);
    explicit dtkZipReader(QIODevice *device);
            ~dtkZipReader(void);

    QIODevice* device(void) const;

    bool isReadable(void) const;
    bool exists(void) const;

    QList<FileInfo> fileInfoList(void) const;

    int count(void) const;

    FileInfo entryInfoAt(int index) const;
    QByteArray fileData(const QString &fileName) const;
    bool extractAll(const QString &destinationDir) const;

    Status status(void) const;

    void close(void);

private:
    dtkZipReaderPrivate *d;

    Q_DISABLE_COPY(dtkZipReader)
};

#endif

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

/*******************************************************************
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**********************************************************************/
