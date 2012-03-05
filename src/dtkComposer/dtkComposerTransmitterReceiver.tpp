/* dtkComposerTransmitterReceiver.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 12:56:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 23:29:54 2012 (+0100)
 *           By: tkloczko
 *     Update #: 97
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

    foreach(dtkComposerTransmitter *v, variants)
        if (v->active())
            return *(static_cast<T *>(v->variant()));
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

    foreach(dtkComposerTransmitter *v, variants)
        if (v->active())
            return *(static_cast<T *>(v->variant()));
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

//! Returns.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiver<T>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
};

template <typename T> QVariant::Type dtkComposerTransmitterReceiver<T>::type(void) const
{
    return dtkComposerTransmitterVariantType(this->data());
};

template <typename T> QString dtkComposerTransmitterReceiver<T>::kindName(void) const
{
    return "Receiver";
};

template <typename T> QString dtkComposerTransmitterReceiver<T>::typeName(void) const
{
    return dtkComposerTransmitterVariantName(this->data());
};

//! Returns
/*! 
 *  
 */
template <typename T> void *dtkComposerTransmitterReceiver<T>::variant(void)
{
    return static_cast<void *>(&(this->data()));
};

//! Returns
/*! 
 *  
 */
template <typename T> const void *dtkComposerTransmitterReceiver<T>::variant(void) const
{
    return static_cast<const void *>(&(this->data()));
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::connect(dtkComposerTransmitter *transmitter)
{
    dtkComposerTransmitterEmitter<T> *emitter = NULL;

    if (transmitter->kind() == Emitter) {
     
        if (emitter = dynamic_cast<dtkComposerTransmitterEmitter<T> *>(transmitter)) {
            if (!emitters.contains(emitter)) {
                emitters << emitter;
                return true;
            }
        }

    } else if (transmitter->kind() == Variant) {

        //if (transmitter->type() == this->type() && !variants.contains(transmitter)) {
            variants << transmitter;
            return true;
            //}
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
