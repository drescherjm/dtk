/* dtkDistributedCommunicatorPluginFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:26:55 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
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

dtkDistributedCommunicatorPluginFactory::dtkDistributedCommunicatorPluginFactory(void) : d(new dtkDistributedCommunicatorPluginFactoryPrivate)
{

}

dtkDistributedCommunicatorPluginFactory::~dtkDistributedCommunicatorPluginFactory(void)
{
    delete d;

    d = NULL;
}
