/* dtkComposerTransmitterReceiver.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 12:56:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu May 10 10:50:16 2012 (+0200)
 *           By: tkloczko
 *     Update #: 212
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
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{
    T t;
    d->variant = qVariantFromValue(t);

    active_emitter = NULL;
    active_variant = NULL;
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{

};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> const T& dtkComposerTransmitterReceiver<T>::data(void)
{
    if (active_emitter)
        return active_emitter->data();

    if (active_variant)
        m_data = qvariant_cast<T>(active_variant->data());

    return m_data;
};

//! 
/*! 
 *  
 */
template <typename T> const dtkAbstractContainer& dtkComposerTransmitterReceiver<T>::container(void) const
{
    if (active_emitter)
        return active_emitter->container();

    if (active_variant)
        return active_variant->container();

    return d->container;
};

//! 
/*! 
 *  
 */
template <typename T> const dtkContainerVector<T>& dtkComposerTransmitterReceiver<T>::vector(void) const
{
    if (active_emitter)
        return active_emitter->vector();

    if (active_variant) 
        return *reinterpret_cast<const dtkContainerVector<T> *>(&(active_variant->container()));

    return m_vector;
};

//! 
/*! 
 *  
 */
template <typename T> const dtkContainerList<T>& dtkComposerTransmitterReceiver<T>::list(void) const
{
    if (active_emitter)
        return active_emitter->list();

    if (active_variant) 
        return *reinterpret_cast<const dtkContainerList<T> *>(&(active_variant->container()));

    return m_list;
};

//! Returns.
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::isEmpty(void) const
{
    if (emitters.isEmpty() && variants.isEmpty())
        return true;

    return false;
};

//! Returns the kind of the transmitter.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiver<T>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
};

template <typename T> QString dtkComposerTransmitterReceiver<T>::kindName(void) const
{
    return "Receiver";
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::connect(dtkComposerTransmitter *transmitter)
{
    dtkComposerTransmitterEmitter<T> *emitter = NULL;

    if (transmitter->kind() == Emitter) {
     
        if ((emitter = dynamic_cast<dtkComposerTransmitterEmitter<T> *>(transmitter))) {
            if (!emitters.contains(emitter)) {
                emitters << emitter;
                active_emitter = emitter;
                active_variant = NULL;
                emitter->appendReceiver(this);
                return true;
            }
        }

    } else if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if(v->types().isEmpty() && !variants.contains(v)) {
            variants << v;
            active_variant = v;
            active_emitter = NULL;
            v->appendReceiver(this);
            return true;
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (t == this->type() && !variants.contains(v)) {
                    variants << v;
                    active_variant = v;
                    active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
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
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);

        ok = variants.removeOne(v);

        if (v == active_variant) {

            active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, variants) {
                if (var->active())
                    active_variant = var;
            }

            if (!active_variant) {
                foreach(dtkComposerTransmitterEmitter<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }
            }
        }

    } else {
    
        dtkComposerTransmitterEmitter<T> *emitter = NULL;

        if ((emitter = dynamic_cast<dtkComposerTransmitterEmitter<T> *>(transmitter))) {

            ok = emitters.removeOne(emitter);

            if (emitter == active_emitter) {

                active_emitter = NULL;

                foreach(dtkComposerTransmitterEmitter<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }

                if (!active_emitter) {
                    foreach(dtkComposerTransmitterVariant *var, variants) {
                        if (var->active())
                            active_variant = var;
                    }
                }
            }
        }
    }

    return ok;
};

//! 
/*! 
 *  
 */
template <typename T> void dtkComposerTransmitterReceiver<T>::setActiveEmitter(dtkComposerTransmitter *emitter)
{
    active_emitter = NULL;
    active_variant = NULL;

    foreach(dtkComposerTransmitterEmitter<T> *e, emitters) {
        if (emitter == static_cast<dtkComposerTransmitter *>(e)) {
            active_emitter = e;
            return;
        }
    }
    
    foreach(dtkComposerTransmitterVariant *v, variants) {
        if (emitter == static_cast<dtkComposerTransmitter *>(v)) {
            active_variant = v;
            return;
        }
    }
}

//! 
/*! 
 *  All links from every receiver found to \a transmitter are stored
 *  in a multi-hash table.
 *
 *  By default, an empty multi-hash is returned.
 */
template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterReceiver<T>::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

#endif
