/* dtkPlugin.cpp --- 
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:00:58 2012 (+0200)
 *           By: tkloczko
 *     Update #: 83
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkPlugin.h"

#include "dtkAbstractDataFactory.h"
#include "dtkAbstractProcessFactory.h"
#include "dtkAbstractViewFactory.h"

// /////////////////////////////////////////////////////////////////
// dtkPluginPrivate
// /////////////////////////////////////////////////////////////////

class dtkPluginPrivate
{
public:
    dtkAbstractViewFactory *viewSingletonFactory;
    dtkAbstractDataFactory *dataSingletonFactory;
    dtkAbstractProcessFactory *processSingletonFactory;

};

// /////////////////////////////////////////////////////////////////
// dtkPlugin
// /////////////////////////////////////////////////////////////////

dtkPlugin::dtkPlugin(QObject *parent) : dtkAbstractObject(), d(new dtkPluginPrivate)
{
    DTK_UNUSED(parent);
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
