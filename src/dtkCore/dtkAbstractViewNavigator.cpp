/* dtkAbstractViewNavigator.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:38:31 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 15:27:30 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
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
#include <dtkCore/dtkAbstractViewNavigator.h>
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractViewNavigatorPrivate
{
public:
    bool enabled;

    dtkSmartPointer <dtkAbstractData> data;

    dtkAbstractView *view;
};

dtkAbstractViewNavigator::dtkAbstractViewNavigator(void) : dtkAbstractObject(), d(new dtkAbstractViewNavigatorPrivate)
{
    d->enabled = false;
    d->view = NULL;
}

dtkAbstractViewNavigator::~dtkAbstractViewNavigator(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractViewNavigator::enabled(void) const
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
