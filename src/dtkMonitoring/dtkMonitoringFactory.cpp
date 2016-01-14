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

void dtkMonitoringFactory::registerCreator(const QString& type, dtkMonitorCreator creator)
{
    d->creators.insert(type, creator);
}

dtkMonitor *dtkMonitoringFactory::create(const QString& type)
{
    return d->creators.values(type).first()(type);
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
