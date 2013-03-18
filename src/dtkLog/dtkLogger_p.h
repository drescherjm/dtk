/* dtkLogger_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:26:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 18 12:25:46 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 50
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
                                    dtkLog::Level  level;
    QHash<dtkLogDestinationPointer, dtkLog::Level> levels;

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
