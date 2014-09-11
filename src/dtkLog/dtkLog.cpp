/* dtkLog.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:40:12 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 18 12:49:06 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 46
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

QString DTKLOG_EXPORT dtkLogPath(QCoreApplication *application)
{
    return QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first()).filePath(QString("%1.log").arg(application->applicationName()));
}
