/* dtkDistributed.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 15:00:12 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:27:09 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Change Log:
 * 
 */

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedCommunicatorPlugin.h"
#include "dtkDistributedCommunicatorPluginFactory.h"
#include "dtkDistributedCommunicatorPluginManager.h"

namespace dtkDistributed
{
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
