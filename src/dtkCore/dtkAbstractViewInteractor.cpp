/* dtkAbstractViewInteractor.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:38:31 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:39:06 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

class dtkAbstractViewInteractorPrivate
{
public:
    bool enabled;
    dtkAbstractData *data;
    dtkAbstractView *view;
};

dtkAbstractViewInteractor::dtkAbstractViewInteractor(void) : dtkAbstractObject(), d(new dtkAbstractViewInteractorPrivate)
{
    d->enabled = false;
    d->data = NULL;
    d->view = NULL;
}

dtkAbstractViewInteractor::~dtkAbstractViewInteractor(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractViewInteractor::enabled(void)
{
    return d->enabled;
}

void dtkAbstractViewInteractor::enable(void)
{
    d->enabled = true;
}

void dtkAbstractViewInteractor::disable(void)
{
    d->enabled = false;
}

void dtkAbstractViewInteractor::setData(dtkAbstractData *data)
{
    d->data = data;
}

void dtkAbstractViewInteractor::setView(dtkAbstractView *view)
{
    d->view = view;
}

dtkAbstractData *dtkAbstractViewInteractor::data(void)
{
    return d->data;
}

dtkAbstractData *dtkAbstractViewInteractor::output(void)
{
    return 0;
}

dtkAbstractData *dtkAbstractViewInteractor::output(int channel)
{
    Q_UNUSED (channel);

    return 0;
}

dtkAbstractData *dtkAbstractViewInteractor::output(int channel, int frame)
{
    Q_UNUSED (channel);
    Q_UNUSED (frame);

    return 0;
}

dtkAbstractView *dtkAbstractViewInteractor::view(void)
{
    return d->view;
}
