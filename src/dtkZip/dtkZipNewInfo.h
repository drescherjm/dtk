/* dtkZipNewInfo.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 15:13:57 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:14:56 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#ifndef DTK_ZIPNEWINFO_H
#define DTK_ZIPNEWINFO_H

#include "dtkZipExport.h"

#include <QtCore>

struct DTKZIP_EXPORT dtkZipNewInfo
{
    QString name;
    QDateTime dateTime;
    quint16 internalAttr;
    quint32 externalAttr;

    QString comment;
    QByteArray extraLocal;
    QByteArray extraGlobal;

    ulong uncompressedSize;

    dtkZipNewInfo(const QString& name);
    dtkZipNewInfo(const QString& name, const QString& file);

    void setFileDateTime(const QString& file);
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
