/* dtkAbstractView_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 16:46:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 13:29:46 2012 (+0200)
 *           By: tkloczko
 *     Update #: 6
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
