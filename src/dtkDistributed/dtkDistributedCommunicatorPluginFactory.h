/* dtkDistributedCommunicatorPluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:17:21 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:26:36 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Change Log:
 * 
 */

#pragma once

class dtkDistributedCommunicatorPluginFactoryPrivate;

class dtkDistributedCommunicatorPluginFactory
{
public:
     dtkDistributedCommunicatorPluginFactory(void);
    ~dtkDistributedCommunicatorPluginFactory(void);

private:
    dtkDistributedCommunicatorPluginFactoryPrivate *d;
};
