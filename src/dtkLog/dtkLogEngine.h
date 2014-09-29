// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

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

//
// dtkLogEngine.h ends here
