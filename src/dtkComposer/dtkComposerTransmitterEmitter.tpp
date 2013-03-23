/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar 23 23:11:28 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 382
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter_p.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterBase
// /////////////////////////////////////////////////////////////////

bool dtkComposerTransmitterEmitterBase::enableCopy(void)
{
    return (d->receivers.count() > 1);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVariant template implementation
// /////////////////////////////////////////////////////////////////

void dtkComposerTransmitterEmitterVariant::setVariant(const QVariant& variant)
{
    d->variant = variant;
}

template <typename T> void dtkComposerTransmitterEmitterVariant::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data));
}

template <typename T> void dtkComposerTransmitterEmitterVariant::setData(T& data)
{
   d->variant.setValue(data);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  Initialize the type of the emitter and the variant that it contains.
 */
template <typename T> dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitterEmitterBase(parent)
{
    d->type_list << qRegisterMetaType<T>(static_cast<T *>(0));
    d->variant = QVariant(d->type_list.first(), 0);
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterEmitter<T>::~dtkComposerTransmitterEmitter(void)
{

};

template <typename T> void dtkComposerTransmitterEmitter<T>::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data)); 
}

template <typename T> void dtkComposerTransmitterEmitter<T>::setData(T& data)
{
    d->variant.setValue(data);
}

template <typename T> int dtkComposerTransmitterEmitter<T>::type(void) const
{
    return d->type_list.first();
}
