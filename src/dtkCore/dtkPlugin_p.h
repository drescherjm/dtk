/* dtkPlugin_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Apr 24 14:44:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 14:45:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLUGIN_P
#define DTKPLUGIN_P

#include "dtkCoreExport.h"
#include "dtkAbstractObject_p.h"


#include "dtkAbstractDataFactory.h"
#include "dtkAbstractProcessFactory.h"
#include "dtkAbstractViewFactory.h"


class dtkPlugin;

////////////////////////////////////////////////////
// dtkPluginPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkPluginPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkPluginPrivate(dtkPlugin *q = 0) : dtkAbstractObjectPrivate(q) {}
    dtkPluginPrivate(const dtkPluginPrivate& other) : dtkAbstractObjectPrivate(other) {}

public:
    dtkAbstractViewFactory *viewSingletonFactory;
    dtkAbstractDataFactory *dataSingletonFactory;
    dtkAbstractProcessFactory *processSingletonFactory;

public:
    virtual ~dtkPluginPrivate(void) {}
};

////////////////////////////////////////////////////
// dtkPlugin protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkPlugin, dtkAbstractObject);

#endif
