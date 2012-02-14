/* dtkComposerReceiver.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 12:56:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 13:14:39 2012 (+0100)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERRECEIVER_TPP
#define DTKCOMPOSERRECEIVER_TPP

#include "dtkComposerEmitter.h"

#include <QString>

// /////////////////////////////////////////////////////////////////
// dtkComposerReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> inline dtkComposerReceiver<T>::dtkComposerReceiver(dtkComposerSceneNode *parent) : dtkComposerTransmitter(parent)
{
    
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> inline dtkComposerReceiver<T>::~dtkComposerReceiver(void)
{

};

//! Connects /a emitter to the receiver.
/*! 
 *  In practice, the emitter is stored in a list of all potential
 *  emitters that can provide the data.
 */
template <typename T> inline void dtkComposerReceiver<T>::connect(dtkComposerEmitter<T> *emitter)
{
    if (!emitters->contains(emitter))
        emitters << emitter;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerReceiver<T>::data(void)
{
    foreach(dtkComposerEmitter<T> *emitter, emitters)
        if (emitter->active())
            return emitter->data();
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerReceiver<T>::data(void) const 
{
    foreach(dtkComposerEmitter<T> *emitter, emitters)
        if (emitter->active())
            return emitter->data();
};

//! Returns description of the receiver.
/*! 
 *  
 */
template <typename T> QString dtkComposerReceiver<T>::identifier(void) const
{
    return "dtkComposerReceiver";
};

#endif
