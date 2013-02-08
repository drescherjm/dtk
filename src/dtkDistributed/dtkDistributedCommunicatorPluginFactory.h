/* dtkDistributedCommunicatorPluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:17:21 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:20:28 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

class dtkDistributedCommunicatorPluginFactoryPrivate;

class dtkDistributedCommunicatorPluginFactory
{
public:
    static dtkDistributedCommunicatorPluginFactory *instance(void);

protected:
     dtkDistributedCommunicatorPluginFactory(void);
    ~dtkDistributedCommunicatorPluginFactory(void);

private:
    static dtkDistributedCommunicatorPluginFactory *s_instance;

private:
    dtkDistributedCommunicatorPluginFactoryPrivate *d;
};
