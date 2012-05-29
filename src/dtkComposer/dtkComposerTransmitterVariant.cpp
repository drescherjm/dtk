/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri May 25 16:22:46 2012 (+0200)
 *           By: tkloczko
 *     Update #: 430
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkContainer/dtkAbstractContainer.h>
#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QList<QVariant::Type> types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    e->twin = NULL;
    e->twinned = false;
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete e;

    e = NULL;
}

void dtkComposerTransmitterVariant::setData(const QVariant& data)
{
    d->variant = data;
    d->container.reset();
}

void dtkComposerTransmitterVariant::setData(const dtkAbstractContainerWrapper& data)
{
    if (d->container != data) {
        d->container = data;
        d->variant = qVariantFromValue(data);
    }
}

QVariant& dtkComposerTransmitterVariant::data(void)
{
    if (e->twinned)
        return d->variant;

    if (e->active_variant)
        return e->active_variant->data();

    if (e->active_emitter)
        return e->active_emitter->variant();

    return d->variant;
}

const QVariant& dtkComposerTransmitterVariant::data(void) const
{
    if (e->twinned)
        return d->variant;

    if (e->active_variant)
        return e->active_variant->data();

    if (e->active_emitter)
        return e->active_emitter->variant();

    return d->variant;
}

QVariantList dtkComposerTransmitterVariant::allData(void)
{
    QVariantList list;

    if (e->twinned) {

        list << d->variant;

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; i++)
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->variant();
            }

        count = e->variants.count();

        for(int i = 0; i < count; i++)
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->data();
            }

    }

    return list;
}

const dtkAbstractContainerWrapper& dtkComposerTransmitterVariant::container(void) const
{
    if (d->container.type() == dtkAbstractContainerWrapper::None) {

        if (e->active_variant)
            d->container = e->active_variant->container();

        else if (e->active_emitter)
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(e->active_emitter->variant());

        else
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(d->variant);
    }      

    return d->container;
}

dtkAbstractContainerWrapper& dtkComposerTransmitterVariant::container(void)
{
    if (d->container.type() == dtkAbstractContainerWrapper::None) {

        if (e->active_variant)
            d->container = e->active_variant->container();

        else if (e->active_emitter)
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(e->active_emitter->variant());

        else
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(d->variant);
    }      

    return d->container;    
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::isEmpty(void) const
{
    if (e->emitters.isEmpty() && e->variants.isEmpty())
        return true;

    return false;
};

void dtkComposerTransmitterVariant::setTwin(dtkComposerTransmitterVariant *twin)
{
    e->twin = twin;
}

dtkComposerTransmitterVariant *dtkComposerTransmitterVariant::twin(void)
{
    return e->twin;
}
    
void dtkComposerTransmitterVariant::setTwinned(bool twinned)
{
    e->twinned = twinned;
}

//! Returns.
/*! 
 *  
 */
dtkComposerTransmitter::Kind dtkComposerTransmitterVariant::kind(void) const
{
    return dtkComposerTransmitter::Variant;
}

QString dtkComposerTransmitterVariant::kindName(void) const
{
    return "Variant";
}

QVariant::Type dtkComposerTransmitterVariant::type(void) const
{
    if (e->twinned)
        return d->variant.type();

    if (e->active_variant)
        return e->active_variant->data().type();

    if (e->active_emitter)
        return e->active_emitter->variant().type();

    return d->variant.type();
}

void dtkComposerTransmitterVariant::setTypes(QList<QVariant::Type> types)
{
    e->types = types;
}

QList<QVariant::Type> dtkComposerTransmitterVariant::types(void)
{
    return e->types;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Variant) {
        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (e->types.isEmpty() || v->types().isEmpty()) {
            if (!e->variants.contains(v)) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;
            }
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (!e->variants.contains(v) && e->types.contains(t)) {
                    e->variants << v;
                    e->active_variant = v;
                    e->active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
        }
    }

    if (e->types.isEmpty() || e->types.contains(transmitter->type())) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            e->active_emitter = transmitter;
            e->active_variant = NULL;
            transmitter->appendReceiver(this);
            return true;
        }
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {
        
        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);
        
        ok = e->variants.removeOne(v);

        if (v == e->active_variant) {

            e->active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, e->variants) {
                if (var->active())
                    e->active_variant = var;
            }
            
            if (!e->active_variant) {
                foreach(dtkComposerTransmitter *em, e->emitters) {
                    if (em->active())
                        e->active_emitter = em;
                }
            }
        }
            
    } else {

        ok = e->emitters.removeOne(transmitter);

        if (transmitter == e->active_emitter) {

            e->active_emitter = NULL;

            foreach(dtkComposerTransmitter *em, e->emitters) {
                if (em->active())
                    e->active_emitter = em;
            }

            if (!e->active_emitter) {
                foreach(dtkComposerTransmitterVariant *var, e->variants) {
                    if (var->active())
                        e->active_variant = var;
                }
            }            

        }
    }    
    
    return ok ;
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitterVariant::setActiveEmitter(dtkComposerTransmitter *emitter)
{
    e->active_emitter = NULL;

    foreach(dtkComposerTransmitter *em, e->emitters) {
        if (emitter == em) {
            e->active_emitter = emitter;
            return;
        }
    }
    
    foreach(dtkComposerTransmitterVariant *v, e->variants) {
        if (emitter == static_cast<dtkComposerTransmitter *>(v)) {
            e->active_variant = v;
            return;
        }
    }
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantContainer implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariantContainer::dtkComposerTransmitterVariantContainer(dtkComposerNode *parent) : dtkComposerTransmitterVariant(parent)
{

}

dtkComposerTransmitterVariantContainer::~dtkComposerTransmitterVariantContainer(void)
{

}

dtkComposerTransmitter::Kind dtkComposerTransmitterVariantContainer::kind(void) const
{
    return dtkComposerTransmitter::VariantContainer;
}

QString dtkComposerTransmitterVariantContainer::kindName(void) const
{
    return "VariantContainer";
}

void dtkComposerTransmitterVariantContainer::setData(const dtkAbstractContainerWrapper& data)
{
    if (d->container != data) {
        d->container = data;
        d->variant = qVariantFromValue(data);
    }
}

const dtkAbstractContainerWrapper& dtkComposerTransmitterVariantContainer::container(void) const
{
    if (d->container.type() == dtkAbstractContainerWrapper::None) {

        if (e->active_variant)
            d->container = e->active_variant->container();

        else if (e->active_emitter)
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(e->active_emitter->variant());

        else
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(d->variant);
    }      

    return d->container;
}

dtkAbstractContainerWrapper& dtkComposerTransmitterVariantContainer::container(void)
{
    if (d->container.type() == dtkAbstractContainerWrapper::None) {

        if (e->active_variant)
            d->container = e->active_variant->container();

        else if (e->active_emitter)
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(e->active_emitter->variant());

        else
            d->container = qvariant_cast<dtkAbstractContainerWrapper>(d->variant);
    }      

    return d->container;    
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariantContainer::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == VariantContainer) {
        dtkComposerTransmitterVariantContainer *v = dynamic_cast<dtkComposerTransmitterVariantContainer *>(transmitter);

        if (e->types.isEmpty() || v->types().isEmpty()) {
            if (!e->variants.contains(v)) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;
            }
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (!e->variants.contains(v) && e->types.contains(t)) {
                    e->variants << v;
                    e->active_variant = v;
                    e->active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
        }
    }

    if (e->types.isEmpty() || e->types.contains(transmitter->type())) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            e->active_emitter = transmitter;
            e->active_variant = NULL;
            transmitter->appendReceiver(this);
            return true;
        }
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariantContainer::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == VariantContainer) {
        
        dtkComposerTransmitterVariantContainer *v = static_cast<dtkComposerTransmitterVariantContainer *>(transmitter);
        
        ok = e->variants.removeOne(v);

        if (v == e->active_variant) {

            e->active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, e->variants) {
                if (var->active())
                    e->active_variant = var;
            }

            if (!e->active_variant) {
                foreach(dtkComposerTransmitter *em, e->emitters) {
                    if (em->active())
                        e->active_emitter = em;
                }
            }
        }

    } else {

        ok = e->emitters.removeOne(transmitter);

        if (transmitter == e->active_emitter) {

            e->active_emitter = NULL;

            foreach(dtkComposerTransmitter *em, e->emitters) {
                if (em->active())
                    e->active_emitter = em;
            }

            if (!e->active_emitter) {
                foreach(dtkComposerTransmitterVariant *var, e->variants) {
                    if (var->active())
                        e->active_variant = var;
                }
            }            

        }
    }    
    
    return ok ;
}
