/* dtkZipWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 23 11:29:30 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 23 13:13:06 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKZIPWRITER_H
#define DTKZIPWRITER_H

#include "dtkZipExport.h"

#include <QtCore/qstring.h>
#include <QtCore/qfile.h>

class dtkZipWriterPrivate;

class DTKZIP_EXPORT dtkZipWriter
{
public:
    enum Status {
        NoError,
        FileWriteError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    enum CompressionPolicy {
        AlwaysCompress,
        NeverCompress,
        AutoCompress
    };

public:
             dtkZipWriter(const QString &fileName, QIODevice::OpenMode mode = (QIODevice::WriteOnly | QIODevice::Truncate));
    explicit dtkZipWriter(QIODevice *device);
            ~dtkZipWriter(void);

    QIODevice* device(void) const;

    bool isWritable(void) const;
    bool exists(void) const;

    Status status(void) const;

    void setCompressionPolicy(CompressionPolicy policy);
    CompressionPolicy compressionPolicy(void) const;

    void setCreationPermissions(QFile::Permissions permissions);
    QFile::Permissions creationPermissions(void) const;

    void addFile(const QString &fileName, const QByteArray &data);
    void addFile(const QString &fileName, QIODevice *device);

    void addDirectory(const QString &dirName);

    void addSymLink(const QString &fileName, const QString &destination);

    void close(void);

private:
    dtkZipWriterPrivate *d;

    Q_DISABLE_COPY(dtkZipWriter)
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
