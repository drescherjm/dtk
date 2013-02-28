/* dtkDistributedCommunicatorPluginFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb 28 14:30:28 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 28
 */

/* Change Log:
 * 
 */

#if 0

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

dtkDistributedCommunicator *dtkDistributedCommunicatorPluginFactory::create(const QString& key)
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


#endif
