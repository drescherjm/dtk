/* dtkPlugin.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 16:31:57 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
#include <dtkCore/dtkPch.h>

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
