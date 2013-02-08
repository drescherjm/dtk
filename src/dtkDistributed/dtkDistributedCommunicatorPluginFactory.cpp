/* dtkDistributedCommunicatorPluginFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:25:11 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#include "dtkDistributedCommunicatorPluginFactory.h"

#include <QtCore>

class dtkDistributedCommunicatorPluginFactoryPrivate
{
public:
};

dtkDistributedCommunicatorPluginFactory *dtkDistributedCommunicatorPluginFactory::instance(void)
{
    if(!s_instance)
	s_instance = new dtkDistributedCommunicatorPluginFactory;

    return s_instance;
}

dtkDistributedCommunicatorPluginFactory::dtkDistributedCommunicatorPluginFactory(void) : d(new dtkDistributedCommunicatorPluginFactoryPrivate)
{

}

dtkDistributedCommunicatorPluginFactory::~dtkDistributedCommunicatorPluginFactory(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicatorPluginFactory *dtkDistributedCommunicatorPluginFactory::s_instance = NULL;
