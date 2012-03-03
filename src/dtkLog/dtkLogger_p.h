/* dtkLogger_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:26:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 22:42:02 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
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

class dtkLoggerPrivate
{
public:
    dtkLog::Level level;

public:
                   dtkLogDestinationPointer  console;
    QHash<QString, dtkLogDestinationPointer> files;

public:
    QList<dtkLogDestinationPointer> destinations;

public:
    QMutex mutex;
};

#endif
