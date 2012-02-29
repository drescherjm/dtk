/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 17:22:29 2012 (+0100)
 *           By: tkloczko
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTEREMITTER_TPP
#define DTKCOMPOSERTRANSMITTEREMITTER_TPP

#include <typeinfo>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

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
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerTransmitterEmitter<T>::data(void)
{
    return m_data;
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerTransmitterEmitter<T>::data(void) const 
{
    return m_data;
};

//! Returns description of the emitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitterEmitter<T>::identifier(void) const
{
    return QString("dtkComposerTransmitterEmitter<%1>").arg(typeid(m_data).name());
};

//! Returns description of the emitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitterEmitter<T>::dataType(void) const
{
    return typeid(m_data).name();
};


template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterEmitter<T>::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};
#endif
