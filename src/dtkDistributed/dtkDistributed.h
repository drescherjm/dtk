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

#include "dtkDistributedExport.h"
#include <QtCore>

class dtkDistributedAbstractApplication;
class dtkDistributedCommunicator;
class dtkDistributedCoreApplication;
class dtkDistributedCommunicatorPlugin;
class dtkDistributedCommunicatorPluginFactory;
class dtkDistributedCommunicatorPluginManager;
class dtkDistributedPolicy;

// ///////////////////////////////////////////////////////////////////
// Distribution layer attributes
// ///////////////////////////////////////////////////////////////////

namespace dtkDistributed
{
#pragma mark -
#pragma mark Distribution namespace flags

    enum Mode {
        Global,
        Local
    };

#pragma mark -
#pragma mark Setting distribution mode

    DTKDISTRIBUTED_EXPORT void setMode(dtkDistributed::Mode);

#pragma mark -
#pragma mark Querying distribution mode

    DTKDISTRIBUTED_EXPORT dtkDistributed::Mode mode(void);

#pragma mark -
#pragma mark retrieve dtkDistributedCoreApplication global pointer

    DTKDISTRIBUTED_EXPORT dtkDistributedAbstractApplication *app(void);

#pragma mark -
#pragma mark create dtkDistributedAbstractApplication application

    DTKDISTRIBUTED_EXPORT dtkDistributedAbstractApplication* create(int &argc, char *argv[]);

#pragma mark -
#pragma mark retrieve current policy

    DTKDISTRIBUTED_EXPORT dtkDistributedPolicy *policy(void);

#pragma mark -
#pragma mark spawn application

    DTKDISTRIBUTED_EXPORT void spawn(void);

#pragma mark -
#pragma mark execute task

    DTKDISTRIBUTED_EXPORT void exec(QRunnable *task);

#pragma mark -
#pragma mark unspawn application

    DTKDISTRIBUTED_EXPORT void unspawn(void);

#pragma mark -
#pragma mark Modular concepts

    namespace communicator {
        DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorPluginFactory& pluginFactory(void);
        DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorPluginManager& pluginManager(void);
        DTKDISTRIBUTED_EXPORT dtkDistributedCommunicator *instance(void);
    }
}

// ///////////////////////////////////////////////////////////////////
// Distribution macros
// ///////////////////////////////////////////////////////////////////

#define DTK_DISTRIBUTED_BEGIN_GLOBAL \
    dtkDistributed::app()->communicator()->barrier(); if (dtkDistributed::communicator::instance()->rank() == 0) {

#define DTK_DISTRIBUTED_END_GLOBAL \
    } ; dtkDistributed::app()->communicator()->barrier();

#define DTK_DISTRIBUTED_BEGIN_LOCAL \
    dtkDistributed::app()->communicator()->barrier();
#define DTK_DISTRIBUTED_END_LOCAL \
    ;

//
// dtkDistributed.h ends here
