/* dtkAbstractViewNavigator.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:38:31 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 01:08:39 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewNavigator.h>

class dtkAbstractViewNavigatorPrivate
{
public:
    bool enabled;
    dtkAbstractData *data;
    dtkAbstractView *view;
};

dtkAbstractViewNavigator::dtkAbstractViewNavigator(void) : dtkAbstractObject(), d(new dtkAbstractViewNavigatorPrivate)
{
    d->enabled = false;
    d->data = NULL;
    d->view = NULL;
}

dtkAbstractViewNavigator::~dtkAbstractViewNavigator(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractViewNavigator::enabled(void)
{
    return d->enabled;
}

void dtkAbstractViewNavigator::enable(void)
{
    d->enabled = true;
}

void dtkAbstractViewNavigator::disable(void)
{
    d->enabled = false;
}

void dtkAbstractViewNavigator::setData(dtkAbstractData *data)
{
    d->data = data;
}

void dtkAbstractViewNavigator::setView(dtkAbstractView *view)
{
    d->view = view;
}

dtkAbstractData *dtkAbstractViewNavigator::data(void)
{
    return d->data;
}

dtkAbstractData *dtkAbstractViewNavigator::output(void)
{
    return 0;
}

dtkAbstractData *dtkAbstractViewNavigator::output(int channel)
{
    return 0;
}

dtkAbstractData *dtkAbstractViewNavigator::output(int channel, int frame)
{
    DTK_UNUSED (channel);
    DTK_UNUSED (frame);

    return 0;
}

dtkAbstractView *dtkAbstractViewNavigator::view(void)
{
    return d->view;
}
