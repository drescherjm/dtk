/* dtkLogger_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:26:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 10:03:15 2012 (+0200)
 *           By: tkloczko
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGGER_P_H
#define DTKLOGGER_P_H

#include "dtkLog.h"
#include "dtkLogDestination.h"

#include <QtCore>
#include <QtGui>

class dtkLogViewList;

class dtkLoggerPrivate
{
public:
    dtkLog::Level level;

public:
                            dtkLogDestinationPointer  console;
    QHash<QString,          dtkLogDestinationPointer> files;
    QHash<QPlainTextEdit *, dtkLogDestinationPointer> editors;
    QHash<dtkLogModel *,    dtkLogDestinationPointer> models;

public:
    QList<dtkLogDestinationPointer> destinations;

public:
    QMutex mutex;
};

#endif
