/* dtkLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:40:12 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 13:24:35 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 48
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
    return QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).filePath(QString("%1.log").arg(application->applicationName()));
}
