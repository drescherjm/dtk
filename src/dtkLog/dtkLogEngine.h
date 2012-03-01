/* dtkLogEngine.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 16:15:38 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 16:58:30 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
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
     dtkLogEngine(dtkLog::Level level);
    ~dtkLogEngine(void);

public:
    QDebug stream(void);

private:
    dtkLogEnginePrivate *d;
};

#endif
