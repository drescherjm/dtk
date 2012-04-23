/* dtkAbstractProcess_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 16:39:35 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 16:40:40 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTPROCESS_P_H
#define DTKABSTRACTPROCESS_P_H

#include "dtkCoreExport.h"
#include "dtkAbstractObject_p.h"

////////////////////////////////////////////////////
// dtkAbstractProcessPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractProcessPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkAbstractProcessPrivate(void) : dtkAbstractObjectPrivate() {}
    dtkAbstractProcessPrivate(const dtkAbstractProcessPrivate& other) : dtkAbstractObjectPrivate(other) {}

public:
    virtual ~dtkAbstractProcessPrivate(void) {}
};

////////////////////////////////////////////////////
// dtkAbstractProcess protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractProcess, dtkAbstractObject);

#endif
