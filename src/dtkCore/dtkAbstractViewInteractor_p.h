/* dtkAbstractViewInteractor_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Apr 24 12:55:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 13:28:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTVIEWINTERACTOR_P_H
#define DTKABSTRACTVIEWINTERACTOR_P_H

#include "dtkCoreExport.h"

#include "dtkAbstractObject_p.h"
#include "dtkSmartPointer.h"

class dtkAbstractViewInteractor;
class dtkAbstractView;

////////////////////////////////////////////////////
// dtkAbstractViewPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractViewInteractorPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkAbstractViewInteractorPrivate(dtkAbstractViewInteractor *q = 0) : dtkAbstractObjectPrivate(q) {}
    dtkAbstractViewInteractorPrivate(const dtkAbstractViewInteractorPrivate& other) : dtkAbstractObjectPrivate(other),
                                                                                      enabled(other.enabled),
                                                                                      data(other.data),
                                                                                      view(other.view) {}

public:
    virtual ~dtkAbstractViewInteractorPrivate(void) {}

public:
    bool enabled;

public:
    dtkSmartPointer<dtkAbstractData> data;

public:
    dtkAbstractView *view;
};

////////////////////////////////////////////////////
// dtkAbstractViewInteractor protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractViewInteractor, dtkAbstractObject);

#endif
