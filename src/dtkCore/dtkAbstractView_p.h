/* dtkAbstractView_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 16:46:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 19:47:57 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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
#include "dtkSmartPointer.h"

class dtkAbstractView;
class dtkAbstractViewAnimator;
class dtkAbstractViewNavigator;
class dtkAbstractViewInteractor;

////////////////////////////////////////////////////
// dtkAbstractViewPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractViewPrivate : public dtkAbstractObjectPrivate
{
public:
    dtkAbstractViewPrivate(dtkAbstractView *q = 0) : dtkAbstractObjectPrivate(q) {}
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
