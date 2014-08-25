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

#include "dtkLog"
#include "dtkLogExport.h"

#include <QtCore>
#include <QtDebug>

DTKLOG_EXPORT void   dtkInstallLoggerHandler(dtkLog::HandlerFlags);
DTKLOG_EXPORT void dtkUninstallLoggerHandler(void);

//
// dtkLoggerHandlers.h ends here
