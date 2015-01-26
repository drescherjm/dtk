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

inline bool dtkComposerTransmitterEmitterBase::enableCopy(void)
{
    return (d->receivers.count() > 1);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVariant template implementation
// /////////////////////////////////////////////////////////////////

inline void dtkComposerTransmitterEmitterVariant::setVariant(const QVariant& variant)
{
    d->variant = variant;
}

template <typename T> inline void dtkComposerTransmitterEmitterVariant::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data));
}

template <typename T> inline void dtkComposerTransmitterEmitterVariant::setData(T& data)
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
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitterEmitterBase(parent)
{
    dtkComposerTransmitterHandler<T>::init(*this);
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::~dtkComposerTransmitterEmitter(void)
{

};

template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data)); 
}

template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(T& data)
{
    d->variant.setValue(data);
}

template <typename T> inline int dtkComposerTransmitterEmitter<T>::type(void) const
{
    return d->type_list.first();
}

template <typename T> inline bool dtkComposerTransmitterEmitter<T>::enableConnection(dtkComposerTransmitter *transmitter)
{
    return dtkComposerTransmitterHandler<T>::enableConnection(*transmitter);
}

// 
// dtkComposerTransmitterEmitter.tpp ends here
