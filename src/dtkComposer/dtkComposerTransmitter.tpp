/* dtkComposerTransmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:14:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 14:19:51 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTER_TPP
#define DTKCOMPOSERTRANSMITTER_TPP

#include <QtCore/QString>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty transmitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter<T>::dtkComposerTransmitter(dtkComposerSceneNode *parent) : dtkComposerAbstractTransmitter(parent), d(new dtkComposerTransmitterPrivate<T>)
{

};

//! Destroys the transmitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter<T>::~dtkComposerTransmitter(void)
{

};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitter<T>::setData(const T& data)
{
    d->data = data;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerTransmitter<T>::data(void)
{
    return d->data;
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerTransmitter<T>::data(void) const 
{
    return d->data;
};

//! Returns description of the transmitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitter<T>::identifier(void) const
{
    return "dtkComposerTransmitter";
};

#endif
