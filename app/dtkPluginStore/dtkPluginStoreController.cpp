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

#include "dtkPluginStoreController.h"

#include <dtkConfig>

dtkPluginStoreController::dtkPluginStoreController(void)
{

}

dtkPluginStoreController::~dtkPluginStoreController(void)
{

}

QString dtkPluginStoreController::arch(void)
{
    QString arch;

#if defined(DTK_BUILD_32)
    arch = "32";
#else
    arch = "64";
#endif

    return arch;
}

QString dtkPluginStoreController::os(void)
{
    QString os;

#if defined(Q_OS_MAC)
    os = "mac";
#endif

#if defined(Q_OS_WIN)
    os = "win";
#endif

#if defined(Q_OS_LINUX)
    os = "lin";
#endif

    return os;
}

//
// dtkPluginStoreController.cpp ends here
