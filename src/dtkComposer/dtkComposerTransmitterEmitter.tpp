// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterHandler.h"

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
    dtkComposerTransmitterHandler<T>::init(*this);
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

template <typename T> bool dtkComposerTransmitterEmitter<T>::enableConnection(dtkComposerTransmitter *transmitter)
{
    return dtkComposerTransmitterHandler<T>::enableConnection(*transmitter);
}

// 
// dtkComposerTransmitterEmitter.tpp ends here
