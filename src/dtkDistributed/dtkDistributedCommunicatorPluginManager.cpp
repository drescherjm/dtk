/* dtkDistributedCommunicatorPluginManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:51:32 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:24:55 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Change Log:
 * 
 */

#include "dtkDistributed.h"
#include "dtkDistributedCommunicatorPlugin.h"
#include "dtkDistributedCommunicatorPluginManager.h"
#include "dtkDistributedSettings.h"

void dtkDistributedCommunicatorPluginManager::initialize(void)
{
    dtkDistributedSettings settings;
    
    dtkCorePluginManager::initialize(settings.value("plugins").toString());
}

void dtkDistributedCommunicatorPluginManager::load(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;

    if(!d->check(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);

    if(dtkDistributedCommunicatorPlugin *plugin = qobject_cast<dtkDistributedCommunicatorPlugin *>(loader->instance()))
        d->loaders.insert(path, loader);
    else
        delete loader;
}
