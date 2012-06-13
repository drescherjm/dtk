/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jun  8 15:15:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 203
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTEREMITTER_TPP
#define DTKCOMPOSERTRANSMITTEREMITTER_TPP

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkContainer/dtkContainerVectorWrapper.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{
    d->variant = qVariantFromValue(m_data);
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::~dtkComposerTransmitterEmitter(void)
{

};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(const T& data)
{
    m_data = data; 
    d->variant = qVariantFromValue(m_data);

    d->count = d->receivers.count();
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerTransmitterEmitter<T>::data(void)
{
    return m_data;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline const T& dtkComposerTransmitterEmitter<T>::data(void) const
{
    return m_data;
};

//! Returns.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter::Kind dtkComposerTransmitterEmitter<T>::kind(void) const
{
    return dtkComposerTransmitter::Emitter;
};

template <typename T> inline QString dtkComposerTransmitterEmitter<T>::kindName(void) const
{
    return "Emitter";
};

template <typename T> inline void dtkComposerTransmitterEmitter<T>::clear(void)
{
    if (d->count.fetchAndAddOrdered(-1)-1) {
        m_data = T();
        d->variant.clear();
        d->container.clear();
    }
}

template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterEmitter<T>::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVector implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::dtkComposerTransmitterEmitterVector(dtkComposerNode *parent) : dtkComposerTransmitterEmitter<T>(parent)
{

};

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::~dtkComposerTransmitterEmitterVector(void)
{

};

template <typename T> inline dtkComposerTransmitter::Kind dtkComposerTransmitterEmitterVector<T>::kind(void) const
{
    return dtkComposerTransmitter::EmitterVector;
};

template <typename T> inline QString dtkComposerTransmitterEmitterVector<T>::kindName(void) const
{
    return "EmitterContainer";
};

template <typename T> inline void dtkComposerTransmitterEmitterVector<T>::clear(void)
{
    if (d->count.fetchAndAddOrdered(-1)-1) {
        m_vector = dtkContainerVector<T>();
        d->container.clear();
        d->variant.clear();
    }
}

template <typename T> inline void dtkComposerTransmitterEmitterVector<T>::setData(const dtkContainerVector<T>& vector)
{
    m_vector = vector;
    d->container = dtkContainerVectorWrapper<T>(m_vector);
    d->variant = qVariantFromValue(d->container);
    
    d->count = d->receivers.count();
};

template <typename T> inline dtkContainerVector<T>& dtkComposerTransmitterEmitterVector<T>::data(void)
{
    return m_vector;
};

template <typename T> inline const dtkContainerVector<T>& dtkComposerTransmitterEmitterVector<T>::data(void) const
{
    return m_vector;
};

#endif
