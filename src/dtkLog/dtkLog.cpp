/* dtkLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:40:12 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 12:58:55 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLog.h"

#include <QtCore>
#include <QtGui>

QString dtkLogPath(QCoreApplication *application)
{
    return QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation)).filePath(QString("%1.log").arg(application->applicationName()));
}
