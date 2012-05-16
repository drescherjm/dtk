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
    DTK_D(dtkPlugin);
    d->viewSingletonFactory = dtkAbstractViewFactory::instance();
    d->dataSingletonFactory = dtkAbstractDataFactory::instance();
    d->processSingletonFactory = dtkAbstractProcessFactory::instance();

}

// /////////////////////////////////////////////////////////////////
// dtkPlugin
// /////////////////////////////////////////////////////////////////
    
dtkPlugin::dtkPlugin(const dtkPlugin& other) : dtkAbstractObject(*new dtkPluginPrivate(*other.d_func()), other)
{
    DTK_D(dtkPlugin);

    d->viewSingletonFactory = dtkAbstractViewFactory::instance();
    d->dataSingletonFactory = dtkAbstractDataFactory::instance();
    d->processSingletonFactory = dtkAbstractProcessFactory::instance();
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
    DTK_D(dtkPlugin);

    return d->viewSingletonFactory;
}

void dtkPlugin::setViewFactorySingleton(dtkAbstractViewFactory *viewSingletonFactory)
{
    DTK_D(dtkPlugin);

    d->viewSingletonFactory = viewSingletonFactory;
}

dtkAbstractDataFactory *dtkPlugin::dataFactorySingleton(void)
{
    DTK_D(dtkPlugin);

    return d->dataSingletonFactory;
}

void dtkPlugin::setDataFactorySingleton(dtkAbstractDataFactory *dataSingletonFactory)
{
    DTK_D(dtkPlugin);

    d->dataSingletonFactory = dataSingletonFactory;
}

dtkAbstractProcessFactory *dtkPlugin::processFactorySingleton(void)
{
    DTK_D(dtkPlugin);

    return d->processSingletonFactory;
}

void dtkPlugin::setProcessFactorySingleton(dtkAbstractProcessFactory *processSingletonFactory)
{
    DTK_D(dtkPlugin);

    d->processSingletonFactory = processSingletonFactory;
}
