/* dtkDistributed.cpp ---
 *
 * Author: Julien Wintz
 * Created: Mon Feb 11 15:00:12 2013 (+0100)
 */

/* Change Log:
 *
 */

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"

// #include "dtkDistributedCommunicatorPlugin.h"
// #include "dtkDistributedCommunicatorPluginFactory.h"
// #include "dtkDistributedCommunicatorPluginManager.h"

namespace dtkDistributed
{
    namespace _private {
        dtkDistributed::Mode mode = dtkDistributed::Global;
    }

    void setMode(dtkDistributed::Mode mode) {
        _private::mode = mode;
    }

    dtkDistributed::Mode mode(void) {
        return _private::mode;
    }

    namespace communicator {

        namespace _private {
            dtkDistributedCommunicatorPluginFactory factory;
            dtkDistributedCommunicatorPluginManager manager;
        }

        dtkDistributedCommunicatorPluginFactory& pluginFactory(void) {
            return _private::factory;
        }

        dtkDistributedCommunicatorPluginManager& pluginManager(void) {
            return _private::manager;
        }
    }
}
