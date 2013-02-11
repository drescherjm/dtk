/* dtkDistributedCommunicatorPluginFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 18:35:40 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Change Log:
 * 
 */

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedCommunicatorPluginFactory.h"

class dtkDistributedCommunicatorPluginFactoryPrivate
{
public:
    QHash<QString, dtkDistributedCommunicatorPluginFactory::creator> creators;
};

dtkDistributedCommunicatorPluginFactory::dtkDistributedCommunicatorPluginFactory(void) : d(new dtkDistributedCommunicatorPluginFactoryPrivate)
{
    
}

dtkDistributedCommunicatorPluginFactory::~dtkDistributedCommunicatorPluginFactory(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicator dtkDistributedCommunicatorPluginFactory::create(const QString& key)
{
    Q_ASSERT(d->creators.contains(key));

    return d->creators.value(key)();
}

QStringList dtkDistributedCommunicatorPluginFactory::keys(void)
{
    return d->creators.keys();
}

void dtkDistributedCommunicatorPluginFactory::record(QString key, creator func)
{
    d->creators.insert(key, func);
}
