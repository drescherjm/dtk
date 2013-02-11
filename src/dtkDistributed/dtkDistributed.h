/* dtkDistributed.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 13:45:24 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:27:14 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
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
    namespace communicator {
	dtkDistributedCommunicatorPluginFactory& pluginFactory(void);
	dtkDistributedCommunicatorPluginManager& pluginManager(void);	
    }
}
