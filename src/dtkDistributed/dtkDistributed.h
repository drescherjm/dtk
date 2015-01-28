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

    DTKDISTRIBUTED_EXPORT dtkDistributedCoreApplication *app(void);

#pragma mark -
#pragma mark retrieve current policy

    DTKDISTRIBUTED_EXPORT dtkDistributedPolicy *policy(void);

#pragma mark -
#pragma mark Modular concepts

    namespace communicator {
        DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorPluginFactory& pluginFactory(void);
        DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorPluginManager& pluginManager(void);
    }
}

// ///////////////////////////////////////////////////////////////////
// Distribution macros
// ///////////////////////////////////////////////////////////////////

#define DTK_DISTRIBUTED_BEGIN_GLOBAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Global); dtkDistributedWork::worker()->setMode(dtkDistributed::mode()); if (dtkDistributedWork::worker()->master()) {

#define DTK_DISTRIBUTED_END_GLOBAL \
    } ; barrier();

#define DTK_DISTRIBUTED_BEGIN_LOCAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Local); dtkDistributedWork::worker()->setMode(dtkDistributed::mode());

#define DTK_DISTRIBUTED_END_LOCAL \
    ;

//
// dtkDistributed.h ends here
