/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 19 14:52:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 275
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
    QList<QVariant::Type> types;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{

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

        if(e->types.isEmpty() && !e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            return true;
        } else if(v->types().isEmpty() && !e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            return true;
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (!e->emitters.contains(transmitter) && e->types.contains(t)) {
                    e->emitters << transmitter;
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
