/* dtkPlugin.cpp --- 
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 15:02:37 2012 (+0200)
 *           By: tkloczko
 *     Update #: 90
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkPlugin.h"
#include "dtkPlugin_p.h"

#include "dtkAbstractDataFactory.h"
#include "dtkAbstractProcessFactory.h"
#include "dtkAbstractViewFactory.h"

// /////////////////////////////////////////////////////////////////
// dtkPlugin implementation
// /////////////////////////////////////////////////////////////////

dtkPlugin::dtkPlugin(QObject *parent) : dtkAbstractObject(*new dtkPluginPrivate(this), parent)
{
<<<<<<< HEAD
public:
    dtkAbstractViewFactory *viewSingletonFactory;
    dtkAbstractDataFactory *dataSingletonFactory;
    dtkAbstractProcessFactory *processSingletonFactory;

};

// /////////////////////////////////////////////////////////////////
// dtkPlugin
// /////////////////////////////////////////////////////////////////
=======
    
}
>>>>>>> cdf41cfcdde4be758fe34ac384f60a3eea379c85

dtkPlugin::dtkPlugin(const dtkPlugin& other) : dtkAbstractObject(*new dtkPluginPrivate(*other.d_func()), other)
{
<<<<<<< HEAD
    DTK_UNUSED(parent);
    d->viewSingletonFactory = dtkAbstractViewFactory::instance();
    d->dataSingletonFactory = dtkAbstractDataFactory::instance();
    d->processSingletonFactory = dtkAbstractProcessFactory::instance();
=======
>>>>>>> cdf41cfcdde4be758fe34ac384f60a3eea379c85

}

dtkPlugin::~dtkPlugin(void)
{

}

QString dtkPlugin::contact(void) const
{
    return QString();
}

QString dtkPlugin::version(void) const
{
    return QString();
}

QStringList dtkPlugin::authors(void) const
{
    return QStringList();
}

QStringList dtkPlugin::contributors(void) const
{
    return QStringList();
}

QStringList dtkPlugin::dependencies(void) const
{
    return QStringList();
}


dtkAbstractViewFactory *dtkPlugin::viewFactorySingleton(void)
{
    return d->viewSingletonFactory;
}

void dtkPlugin::setViewFactorySingleton(dtkAbstractViewFactory *viewSingletonFactory)
{
    d->viewSingletonFactory = viewSingletonFactory;
}

dtkAbstractDataFactory *dtkPlugin::dataFactorySingleton(void)
{
    return d->dataSingletonFactory;
}

void dtkPlugin::setDataFactorySingleton(dtkAbstractDataFactory *dataSingletonFactory)
{
    d->dataSingletonFactory = dataSingletonFactory;
}

dtkAbstractProcessFactory *dtkPlugin::processFactorySingleton(void)
{
    return d->processSingletonFactory;
}

void dtkPlugin::setProcessFactorySingleton(dtkAbstractProcessFactory *processSingletonFactory)
{
    d->processSingletonFactory = processSingletonFactory;
}
