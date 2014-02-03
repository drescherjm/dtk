/* dtkLogEngine.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 16:15:38 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 18 12:33:03 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGENGINE_H
#define DTKLOGENGINE_H

#include "dtkLog.h"
#include "dtkLogExport.h"

#include <QtDebug>

class dtkLogEnginePrivate;

class DTKLOG_EXPORT dtkLogEngine
{
public:
     dtkLogEngine(dtkLog::Level level, bool custom = false);
    ~dtkLogEngine(void);

public:
    QDebug stream(void);

private:
    dtkLogEnginePrivate *d;
};

#endif
