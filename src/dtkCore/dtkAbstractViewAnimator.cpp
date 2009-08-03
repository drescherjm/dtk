/* dtkAbstractViewAnimator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 30 16:14:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 00:46:42 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewAnimator.h>

class dtkAbstractViewAnimatorPrivate
{
public:
    bool enabled;
    dtkAbstractData *data;
    dtkAbstractView *view;
};

dtkAbstractViewAnimator::dtkAbstractViewAnimator(void) : dtkAbstractObject(), d(new dtkAbstractViewAnimatorPrivate)
{
    d->enabled = false;
}

dtkAbstractViewAnimator::~dtkAbstractViewAnimator(void)
{

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

bool dtkAbstractViewAnimator::enabled(void)
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
