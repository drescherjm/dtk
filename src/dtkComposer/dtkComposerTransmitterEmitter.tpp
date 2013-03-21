/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 21 16:56:17 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 362
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter_p.h"

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterBase
// /////////////////////////////////////////////////////////////////

void dtkComposerTransmitterEmitterBase::clearData(void)
{
    d->variant.clear();
}

bool dtkComposerTransmitterEmitterBase::enableCopy(void)
{
    return (d->receivers.count() > 1);
}

void dtkComposerTransmitterEmitterBase::setData(const QVariant& data)
{ 
    d->variant = data; 
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
    d->type = qRegisterMetaType<T>(static_cast<T *>(0));
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterEmitter<T>::~dtkComposerTransmitterEmitter(void)
{

};

template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterEmitter<T>::kind(void) const
{
    return dtkComposerTransmitter::Emitter;
};

template <typename T> QString dtkComposerTransmitterEmitter<T>::kindName(void) const
{
    return "Emitter";
};

template <typename T> void dtkComposerTransmitterEmitter<T>::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data)); 
}

template <typename T> void dtkComposerTransmitterEmitter<T>::setData(T& data)
{
    d->variant.setValue(data);
}
