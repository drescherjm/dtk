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

#include "dtkLogExport.h"

#include <QtCore>

namespace dtkLog {

    enum HandlerFlag {
        Console = 0x00,
           File = 0x01
    };

    Q_DECLARE_FLAGS(HandlerFlags, HandlerFlag);
    Q_DECLARE_OPERATORS_FOR_FLAGS(HandlerFlags);
};

DTKLOG_EXPORT void   dtkInstallLoggerHandler(dtkLog::HandlerFlags);
DTKLOG_EXPORT void dtkUninstallLoggerHandler(void);

// #define qCritical                                                       \
//     for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtCriticalMsg); enabled; enabled = false) \
//         QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).critical

#define dtkDebug    qDebug
#define dtkInfo     qDebug
#define dtkTrace    qDebug
#define dtkError    qDebug
#define dtkWarn     qWarning
#define dtkCritical qCritical

//
// dtkLog.h ends here
