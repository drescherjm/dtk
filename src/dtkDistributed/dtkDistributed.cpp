/* dtkDistributed.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:23:52 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 12:28:59 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#include "dtkDistributed.h"
#include "dtkDistributedCoreApplication.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedPolicy.h"

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

    dtkDistributedCoreApplication *app(void) {
        return dynamic_cast<dtkDistributedCoreApplication *>(dtkDistributedCoreApplication::instance());
    }

    dtkDistributedPolicy *policy(void) {
        dtkDistributedCoreApplication *dsapp = app();
        if (!dsapp)
            return NULL;

        return dsapp->policy();
    }

    namespace communicator
    {
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
