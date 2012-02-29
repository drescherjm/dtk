/* dtkComposerTransmitterReceiver.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 12:56:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 17:24:03 2012 (+0100)
 *           By: tkloczko
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERRECEIVER_TPP
#define DTKCOMPOSERTRANSMITTERRECEIVER_TPP

#include "dtkComposerTransmitterEmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{
    
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{

};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerTransmitterReceiver<T>::data(void)
{
    foreach(dtkComposerTransmitterEmitter<T> *emitter, emitters)
        if (emitter->active())
            return emitter->data();
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerTransmitterReceiver<T>::data(void) const 
{
    foreach(dtkComposerTransmitterEmitter<T> *emitter, emitters)
        if (emitter->active())
            return emitter->data();
};

//! Returns description of the receiver.
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::isEmpty(void) const
{
    if (emitters.isEmpty())
        return true;

    return false;
};

//! Returns description of the receiver.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitterReceiver<T>::identifier(void) const
{
    T fake;
    return QString("dtkComposerTransmitterReceiver<%1>").arg(typeid(fake).name());
};

//! Returns description of the emitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerTransmitterReceiver<T>::dataType(void) const
{
    T fake;
    return typeid(fake).name();
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::connect(dtkComposerTransmitter *transmitter)
{
    dtkComposerTransmitterEmitter<T> *emitter = NULL;

    if (emitter = dynamic_cast<dtkComposerTransmitterEmitter<T> *>(transmitter)) {
        if (!emitters.contains(emitter)) {
            emitters << emitter;
            return true;
        }
    }

    return false;
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::disconnect(dtkComposerTransmitter *transmitter)
{
    dtkComposerTransmitterEmitter<T> *emitter = NULL;

    if (emitter = dynamic_cast<dtkComposerTransmitterEmitter<T> *>(transmitter)) {
        return emitters.removeOne(emitter);
    }

    return false;
};

//! 
/*! 
 *  All links from every receiver found to \a transmitter are stored
 *  in a multi-hash table.
 *
 *  By default, an empty multi-hash is returned.
 */
template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterReceiver<T>::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

#endif
