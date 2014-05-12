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

class dtkDistributedCommunicatorPlugin;
class dtkDistributedCommunicatorPluginFactory;
class dtkDistributedCommunicatorPluginManager;

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

    void setMode(dtkDistributed::Mode);

#pragma mark -
#pragma mark Querying distribution mode

    dtkDistributed::Mode mode(void);

#pragma mark -
#pragma mark Modular concepts

    namespace communicator {
        dtkDistributedCommunicatorPluginFactory& pluginFactory(void);
        dtkDistributedCommunicatorPluginManager& pluginManager(void);
    }
}

// ///////////////////////////////////////////////////////////////////
// Distribution macros
// ///////////////////////////////////////////////////////////////////

#define DTK_DISTRIBUTED_BEGIN_GLOBAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Global); dtkDistributedWork::worker()->setMode(dtkDistributed::mode()); if (dtkDistributedWork::worker()->master()) { time.restart();

#define DTK_DISTRIBUTED_END_GLOBAL \
    qDebug() << "global section:" <<  time.elapsed() << "ms"; } ; barrier();

#define DTK_DISTRIBUTED_BEGIN_LOCAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Local); dtkDistributedWork::worker()->setMode(dtkDistributed::mode()); time.restart();

#define DTK_DISTRIBUTED_END_LOCAL \
    qDebug() << "local section:" <<  time.elapsed() << "ms";

//
// dtkDistributed.h ends here
