/* dtkComposerTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 15:41:22 2012 (+0100)
 *           By: tkloczko
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate
{
public:
    bool active;
    bool required;

    dtkComposerNode *parent;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitter::dtkComposerTransmitter(dtkComposerNode *parent) : d(new dtkComposerTransmitterPrivate)
{
    d->active = true;
    d->required = true;
    d->parent = parent;
}

dtkComposerTransmitter::~dtkComposerTransmitter(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerTransmitter::parentNode(void) const
{
    return d->parent;
}

void dtkComposerTransmitter::activate(void)
{
    d->active = true;
}

void dtkComposerTransmitter::inactivate(void)
{
    d->active = false;
}

bool dtkComposerTransmitter::active(void)
{
    return d->active;
}

void dtkComposerTransmitter::setRequired(bool required)
{
    d->required = required;
}

bool dtkComposerTransmitter::required(void)
{
    return d->required;
}

bool dtkComposerTransmitter::connect(dtkComposerTransmitter *transmitter)
{
    return false;
}

dtkComposerTransmitter::Chains dtkComposerTransmitter::leftChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    return Chains();
}

dtkComposerTransmitter::Chains dtkComposerTransmitter::rightChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    return Chains();
}

bool dtkComposerTransmitter::onTransmittersConnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList valid_links, dtkComposerTransmitterLinkList invalid_links)
{
    dtkComposerTransmitterLinkList list;

    Chains  left_chains =  source->leftChains(destination, list);
    Chains right_chains = destination->rightChains(source, list);

    foreach(dtkComposerTransmitter *receiver, right_chains.uniqueKeys()) {

        foreach(dtkComposerTransmitter *emitter, left_chains.uniqueKeys()) {

            if (receiver->connect(emitter)) {

                foreach(dtkComposerTransmitterLink *l, right_chains.values(receiver))
                    if(!valid_links.contains(l))
                        valid_links << l;
                foreach(dtkComposerTransmitterLink *l, left_chains.values(emitter))
                    if(!valid_links.contains(l))
                        valid_links << l;
            
            } else {

                foreach(dtkComposerTransmitterLink *l, right_chains.values(receiver))
                    if(!invalid_links.contains(l))
                        invalid_links << l;
                foreach(dtkComposerTransmitterLink *l, left_chains.values(emitter))
                    if(!invalid_links.contains(l))
                        invalid_links << l;

            }
        }
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

//! Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter)
{
    debug.nospace() << transmitter.identifier();
    
    return debug.space();
}

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerTransmitter *transmitter)
{
    debug.nospace() << transmitter->identifier();
    
    return debug.space();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLinkPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterLinkPrivate
{
public:
    dtkComposerTransmitter *source;
    dtkComposerTransmitter *destination;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLink implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterLink::dtkComposerTransmitterLink(dtkComposerTransmitter *source, dtkComposerTransmitter *destination) : d(new dtkComposerTransmitterLinkPrivate)
{
    d->source = source;
    d->destination = destination;
}

dtkComposerTransmitterLink::~dtkComposerTransmitterLink(void)
{
    delete d;
    
    d = NULL;
}

dtkComposerTransmitter *dtkComposerTransmitterLink::source(void)
{
    return d->source;
}

dtkComposerTransmitter *dtkComposerTransmitterLink::destination(void)
{
    return d->destination;
}
