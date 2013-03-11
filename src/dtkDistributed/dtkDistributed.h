/* dtkDistributed.h ---
 *
 * Author: Julien Wintz
 * Created: Mon Feb 11 13:45:24 2013 (+0100)
 */

/* Change Log:
 *
 */

#pragma once

class dtkDistributedCommunicatorPlugin;
class dtkDistributedCommunicatorPluginFactory;
class dtkDistributedCommunicatorPluginManager;

#define DTK_DISTRIBUTED_BEGIN_GLOBAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Global); dtkDistributedWork::worker()->setMode(dtkDistributed::mode()); if (dtkDistributedWork::worker()->master()) { time.restart(); 

#define DTK_DISTRIBUTED_END_GLOBAL \
    qDebug() << "global section:" <<  time.elapsed() << "ms"; } ; barrier();

#define DTK_DISTRIBUTED_BEGIN_LOCAL \
    barrier(); dtkDistributed::setMode(dtkDistributed::Local); dtkDistributedWork::worker()->setMode(dtkDistributed::mode()); time.restart();

#define DTK_DISTRIBUTED_END_LOCAL \
    qDebug() << "local section:" <<  time.elapsed() << "ms";

namespace dtkDistributed
{
    enum Mode {
        Global,
        Local
    };

    void setMode(dtkDistributed::Mode);
    dtkDistributed::Mode mode(void);

    namespace communicator {
        dtkDistributedCommunicatorPluginFactory& pluginFactory(void);
        dtkDistributedCommunicatorPluginManager& pluginManager(void);
    }
}
