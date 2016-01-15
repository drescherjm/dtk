// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkMonitor.h"
#include "dtkMonitorBooleanSimple.h"
#include "dtkMonitoringFactory.h"

class dtkMonitoringFactoryPrivate
{
public:
    QMultiHash<QString, dtkMonitoringFactory::dtkMonitorCreator> creators;
};

// /////////////////////////////////////////////////////////////////
// dtkMonitoringFactory
// /////////////////////////////////////////////////////////////////

dtkMonitoringFactory *dtkMonitoringFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkMonitoringFactory;

    return s_instance;
}

void dtkMonitoringFactory::initialize(void)
{
    this->registerCreator("boolean", createMonitor<dtkMonitorBooleanSimple>);
}

void dtkMonitoringFactory::uninitialize(void)
{
    // TODO
}

void dtkMonitoringFactory::registerCreator(const QString& type, dtkMonitorCreator creator)
{
    d->creators.insert(type, creator);
}

dtkMonitor *dtkMonitoringFactory::create(const QString& type)
{
    if(d->creators.values(type).isEmpty())
        return NULL;
    return d->creators.values(type).first()();
}

dtkMonitoringFactory::dtkMonitoringFactory(void)
{
    d = new dtkMonitoringFactoryPrivate;
}

dtkMonitoringFactory::~dtkMonitoringFactory(void)
{
    delete d;
}

dtkMonitoringFactory *dtkMonitoringFactory::s_instance = NULL;

//
// dtkMonitoringFactory.cpp ends here
