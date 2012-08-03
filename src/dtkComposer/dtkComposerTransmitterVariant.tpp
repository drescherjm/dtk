/* dtkComposerTransmitterVariant.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:31:25 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 01:23:11 2012 (+0200)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_TPP
#define DTKCOMPOSERTRANSMITTERVARIANT_TPP

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant_p.h"

#include <dtkContainer/dtkContainerVectorWrapper.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////


template <typename T> inline void dtkComposerTransmitterVariant::setData(T *data)
{
    T t;
    d->type.setValue(t);
    d->variant.setValue(data);
    d->container->reset();
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(dtkContainerVector<T> *data)
{
    dtkAbstractContainerWrapper w;
    d->type.setValue(w);
    d->container = new dtkContainerVectorWrapper<T>(data);
    d->variant.setValue(d->container);
}

template <typename T> inline T *dtkComposerTransmitterVariant::data(void)
{
    if (e->twinned)
        return d->variant.value<T*>();

    if (e->active_variant)
        return e->active_variant->data<T>();

    if (e->active_emitter)
        return e->active_emitter->variant().value<T*>();

    return d->variant.value<T*>();
}

#endif
