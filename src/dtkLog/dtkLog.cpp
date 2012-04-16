/* dtkLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:40:12 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:06:43 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLog.h"
#include "dtkLogExport.h"

#include <QtCore>
#include <QtGui>

QString DTKLOG_EXPORT dtkLogPath(QCoreApplication *application)
{
    return QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation)).filePath(QString("%1.log").arg(application->applicationName()));
}
