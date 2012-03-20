/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 15:14:40 2012 (+0100)
 *           By: tkloczko
 *     Update #: 296
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"

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
    
    if (e->twin)
        e->twin->setData(data);
}

QVariant dtkComposerTransmitterVariant::data(void)
{
    if (e->twinned)
        return d->variant;

    foreach(dtkComposerTransmitter *emitter, e->emitters) {
         if (emitter->active()) {
             return emitter->variant();
        }
    }

    foreach(dtkComposerTransmitterVariant *v, e->variants) {
         if (v->active()) {
             return v->data();
        }
    }

    return d->variant;
}

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

    foreach(dtkComposerTransmitter *emitter, e->emitters) {
         if (emitter->active()) {
             return emitter->variant().type();
        }
    }

    foreach(dtkComposerTransmitterVariant *v, e->variants) {
         if (v->active()) {
             return v->data().type();
        }
    }

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
                return true;
            }
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (!e->variants.contains(v) && e->types.contains(t)) {
                    e->variants << v;
                    return true;
                }
            }            
        }
    }

    if (e->types.isEmpty() || e->types.contains(transmitter->type())) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
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
    return e->emitters.removeOne(transmitter);
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}
