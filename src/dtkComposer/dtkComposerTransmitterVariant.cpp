/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 12:43:53 2012 (+0100)
 *           By: tkloczko
 *     Update #: 250
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

public:
    QVariant::Type type;

public:
    QList<QVariant::Type> types;

public:
    int count_ref;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(QList<QVariant::Type> types, dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{
    e->count_ref = 0;
    e->types = types;
    e->type  = QVariant::Invalid; 
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete e;

    e = NULL;
}

void dtkComposerTransmitterVariant::setData(const QVariant& data)
{
    d->variant = data;
}

QVariant dtkComposerTransmitterVariant::data(void)
{
    foreach(dtkComposerTransmitter *emitter, e->emitters)
        if (emitter->active())
            return emitter->variant();

    return d->variant;
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

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (e->count_ref == 0) {
        if (e->types.contains(transmitter->type())) {
            e->type = transmitter->type();
            e->emitters << transmitter;
            e->count_ref++;
            return true;
        }
    }

    if (transmitter->type() == e->type) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            e->count_ref++;
            return true;
        }
    }

    if (e->types.contains(transmitter->type())) {
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
    if (transmitter->type() == e->type) {
        if (e->emitters.removeOne(transmitter)) {
            if (transmitter->type() == e->type)
                e->count_ref--;
            if (e->count_ref == 0 && e->emitters.count() > 0) {
                e->type = e->emitters.first()->type();
                foreach(dtkComposerTransmitter *t, e->emitters)
                    if (t->type() == e->type)
                        e->count_ref++;
            }
            return true;
        }
    }

    return false;
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
