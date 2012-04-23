/* dtkAbstractView_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 16:46:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 16:53:04 2012 (+0200)
 *           By: tkloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTVIEW_P_H
#define DTKABSTRACTVIEW_P_H

#include "dtkCoreExport.h"
#include "dtkAbstractObject_p.h"
#include "dtkAbstractViewAnimator.h"
#include "dtkAbstractViewNavigator.h"
#include "dtkAbstractViewInteractor.h"
#include "dtkSmartPointer.h"

class dtkAbstractView;

////////////////////////////////////////////////////
// dtkAbstractViewPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractViewPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkAbstractViewPrivate(void) : dtkAbstractObjectPrivate() {}
    dtkAbstractViewPrivate(const dtkAbstractViewPrivate& other) : dtkAbstractObjectPrivate(other),
                                                                  stereo(other.stereo),
                                                                  animators(other.animators),
                                                                  navigators(other.navigators),
                                                                  interactors(other.interactors) {}

public:
    virtual ~dtkAbstractViewPrivate(void) {}

public:
    bool stereo;

public:
    QMap<QString, dtkSmartPointer<dtkAbstractViewAnimator> >   animators;
    QMap<QString, dtkSmartPointer<dtkAbstractViewNavigator> >  navigators;
    QMap<QString, dtkSmartPointer<dtkAbstractViewInteractor> > interactors;
};

////////////////////////////////////////////////////
// dtkAbstractView protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractView, dtkAbstractObject);

#endif
