/* dtkZipFileInfo.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:11:46 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:13:12 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTK_ZIPFILEINFO_H
#define DTK_ZIPFILEINFO_H

#include "dtkZipExport.h"

#include <QtCore>

struct DTKZIP_EXPORT dtkZipFileInfo
{
    QString name;
    quint16 versionCreated;
    quint16 versionNeeded;
    quint16 flags;
    quint16 method;
    QDateTime dateTime;
    quint32 crc;
    quint32 compressedSize;
    quint32 uncompressedSize;
    quint16 diskNumberStart;
    quint16 internalAttr;
    quint32 externalAttr;
    QString comment;
    QByteArray extra;
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
