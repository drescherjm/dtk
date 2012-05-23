/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 16 12:02:32 2012 (+0200)
 *           By: tkloczko
 *     Update #: 161
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

//! 
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setVector(const dtkContainerVector<T>& vector)
{
    if (m_vector != vector) {
        m_vector = vector;
        d->container = m_vector;
        d->variant = qVariantFromValue(d->container);
    }
};

//! 
/*! 
 *  
 */
template <typename T> inline dtkContainerVector<T>& dtkComposerTransmitterEmitter<T>::vector(void)
{
    return m_vector;
};

//! 
/*! 
 *  
 */
template <typename T> inline const dtkContainerVector<T>& dtkComposerTransmitterEmitter<T>::vector(void) const
{
    return m_vector;
};

//! 
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setList(const dtkContainerList<T>& list)
{
    if (m_list != list) {
        m_list = list;
        d->container = m_list;
        d->variant = qVariantFromValue(d->container);
    }
};

//! 
/*! 
 *  
 */
template <typename T> inline dtkContainerList<T>& dtkComposerTransmitterEmitter<T>::list(void)
{
    return m_list;
};

//! 
/*! 
 *  
 */
template <typename T> inline const dtkContainerList<T>& dtkComposerTransmitterEmitter<T>::list(void) const
{
    return m_list;
};

//! Returns.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterEmitter<T>::kind(void) const
{
    return dtkComposerTransmitter::Emitter;
};

template <typename T> QString dtkComposerTransmitterEmitter<T>::kindName(void) const
{
    return "Emitter";
};

template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterEmitter<T>::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

#endif
