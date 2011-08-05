/* dtkAbstractViewAnimator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 30 16:14:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 15:27:15 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
#include <dtkCore/dtkPch.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewAnimator.h>
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractViewAnimatorPrivate
{
public:
    bool enabled;

    dtkSmartPointer<dtkAbstractData> data;

    dtkAbstractView *view;
};

dtkAbstractViewAnimator::dtkAbstractViewAnimator(void) : dtkAbstractObject(), d(new dtkAbstractViewAnimatorPrivate)
{
    d->enabled = false;
    d->view = NULL;
}

dtkAbstractViewAnimator::~dtkAbstractViewAnimator(void)
{
    delete d;

    d = NULL;
}

dtkAbstractData *dtkAbstractViewAnimator::data(void)
{
    return d->data;
}

dtkAbstractView *dtkAbstractViewAnimator::view(void)
{
    return d->view;
}

void dtkAbstractViewAnimator::setData(dtkAbstractData *data)
{
    d->data = data;
}

void dtkAbstractViewAnimator::setView(dtkAbstractView *view)
{
    d->view = view;
}

bool dtkAbstractViewAnimator::enabled(void) const
{
    return d->enabled;
}

void dtkAbstractViewAnimator::enable(void)
{
    d->enabled = true;
}

void dtkAbstractViewAnimator::disable(void)
{
    d->enabled = false;
}

void dtkAbstractViewAnimator::start(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractViewAnimator::stop(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}
