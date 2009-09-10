/* dtkPlugin.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 08:49:25 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 58
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

dtkPlugin::dtkPlugin(QObject * parent) : QObject(parent), d(new dtkPluginPrivate)
{

}

dtkPlugin::~dtkPlugin(void)
{

}
