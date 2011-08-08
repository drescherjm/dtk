/* dtkAbstractViewInteractor.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:38:31 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 15:26:35 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 57
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
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractViewInteractorPrivate
{
public:
    bool enabled;

    dtkSmartPointer<dtkAbstractData> data;

    dtkAbstractView *view;
};

dtkAbstractViewInteractor::dtkAbstractViewInteractor(void) : dtkAbstractObject(), d(new dtkAbstractViewInteractorPrivate)
{
    d->enabled = false;
    d->view = NULL;
}

dtkAbstractViewInteractor::~dtkAbstractViewInteractor(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractViewInteractor::enabled(void) const
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

void dtkAbstractViewInteractor::setData(dtkAbstractData *data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractViewInteractor::setData(dtkAbstractData *data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
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
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

dtkAbstractData *dtkAbstractViewInteractor::output(int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);

    return NULL;
}

dtkAbstractData *dtkAbstractViewInteractor::output(int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);

    return NULL;
}

dtkAbstractView *dtkAbstractViewInteractor::view(void)
{
    return d->view;
}

void dtkAbstractViewInteractor::predraw(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractViewInteractor::draw(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractViewInteractor::postdraw(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}
