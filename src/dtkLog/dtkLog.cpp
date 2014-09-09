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

#include "dtkLog.h"

#include <iostream>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

namespace dtkLogPrivate {

    void   installFileHandler(void);
    void uninstallFileHandler(void);
    void              handler(QtMsgType type, const QMessageLogContext &context, const QString &message);
};

namespace dtkLogPrivate {
                   QFile file;
    dtkLog::HandlerFlags flags;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

namespace dtkLogPrivate {

void installFileHandler(void)
{
    file.setFileName(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first() + "/dtk.log");
    file.open(QIODevice::WriteOnly);
}

void uninstallFileHandler(void)
{
    file.close();
}

void handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    std::cerr << qPrintable(Q_FUNC_INFO);
}

};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkInstallLoggerHandler(dtkLog::HandlerFlags flags)
{
    dtkLogPrivate::flags = flags;

    if (dtkLogPrivate::flags & dtkLog::File)
        dtkLogPrivate::installFileHandler();

    qInstallMessageHandler(dtkLogPrivate::handler);
}


void dtkUninstallLoggerHandler()
{
    if (dtkLogPrivate::flags & dtkLog::File)
        dtkLogPrivate::uninstallFileHandler();

    qInstallMessageHandler(0);
}


//
// dtkLog.cpp ends here
