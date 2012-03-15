/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 18:30:02 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 113
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

    qDebug() << __func__ << d->variant;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T dtkComposerTransmitterEmitter<T>::data(void)
{
    return m_data;
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
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

#endif
