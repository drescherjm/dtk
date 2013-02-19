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
