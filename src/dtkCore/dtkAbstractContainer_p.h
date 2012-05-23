/* dtkAbstractContainer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 16:15:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 16:31:34 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINER_P_H
#define DTKABSTRACTCONTAINER_P_H

#include "dtkCoreExport.h"
#include "dtkAbstractData_p.h"

class dtkAbstractContainer;

////////////////////////////////////////////////////
// dtkAbstractContainerPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractContainerPrivate : public dtkAbstractDataPrivate
{
public:
    dtkAbstractContainerPrivate(dtkAbstractContainer *q = 0) : dtkAbstractDataPrivate(q) {}
    dtkAbstractContainerPrivate(const dtkAbstractContainerPrivate& other) : dtkAbstractDataPrivate(other) {}

public:
    virtual ~dtkAbstractContainerPrivate(void) {}
};

////////////////////////////////////////////////////
// dtkAbstractContainer protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractContainer, dtkAbstractData);

#endif
