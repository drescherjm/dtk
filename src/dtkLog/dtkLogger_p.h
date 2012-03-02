/* dtkLogger_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:26:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  2 18:56:14 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 41
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

class dtkLogViewList;

class dtkLoggerPrivate
{
public:
    dtkLog::Level level;

public:
                            dtkLogDestinationPointer  console;
    QHash<QString,          dtkLogDestinationPointer> files;
    QHash<dtkLogViewList *, dtkLogDestinationPointer> views;

public:
    QList<dtkLogDestinationPointer> destinations;

public:
    QMutex mutex;
};

#endif
