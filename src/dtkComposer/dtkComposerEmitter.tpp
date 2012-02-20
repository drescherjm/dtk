/* dtkComposerEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 14:48:59 2012 (+0100)
 *           By: tkloczko
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREMITTER_TPP
#define DTKCOMPOSEREMITTER_TPP

// /////////////////////////////////////////////////////////////////
// dtkComposerEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerEmitter<T>::dtkComposerEmitter(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{
    
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerEmitter<T>::~dtkComposerEmitter(void)
{

};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerEmitter<T>::setData(const T& data)
{
    m_data = data;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerEmitter<T>::data(void)
{
    return m_data;
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerEmitter<T>::data(void) const 
{
    return m_data;
};

//! Returns description of the emitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerEmitter<T>::identifier(void) const
{
    return "dtkComposerEmitter";
};


template <typename T> dtkComposerTransmitter::Chains dtkComposerEmitter<T>::leftChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    list << new dtkComposerTransmitterLink(this, transmitter);

    Chains chain;
    foreach(dtkComposerTransmitterLink *l, list)
        chain.insert(this, l);

    return chain;
};
#endif
