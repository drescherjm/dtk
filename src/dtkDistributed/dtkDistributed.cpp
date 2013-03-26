/* dtkDistributed.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:23:52 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:23:58 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"

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
