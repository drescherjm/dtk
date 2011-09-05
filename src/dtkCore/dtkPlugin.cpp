/* dtkPlugin.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 13:16:34 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 80
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkPlugin.h>

// /////////////////////////////////////////////////////////////////
// dtkPluginPrivate
// /////////////////////////////////////////////////////////////////

class dtkPluginPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkPlugin
// /////////////////////////////////////////////////////////////////

dtkPlugin::dtkPlugin(QObject *parent) : dtkAbstractObject(), d(new dtkPluginPrivate)
{

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
