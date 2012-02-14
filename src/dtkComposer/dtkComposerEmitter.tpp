/* dtkComposerEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 11:37:57 2012 (+0100)
 *           By: tkloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREMITTER_TPP
#define DTKCOMPOSEREMITTER_TPP

#include <QString>

// /////////////////////////////////////////////////////////////////
// dtkComposerEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerEmitter<T>::dtkComposerEmitter(dtkComposerSceneNode *parent) : dtkComposerTransmitter(parent)
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

#endif
