/* dtkComposerTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 12:50:16 2012 (+0100)
 *           By: tkloczko
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter.h"
#include "dtkComposerSceneNode.h"

#include <QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate
{
public:
    bool active;

    dtkComposerSceneNode *parent;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitter::dtkComposerTransmitter(dtkComposerSceneNode *parent) : d(new dtkComposerTransmitterPrivate)
{
    d->active = true;
    d->parent = parent;
}

dtkComposerTransmitter::~dtkComposerTransmitter(void)
{
    delete d;

    d = NULL;
}

dtkComposerSceneNode *dtkComposerTransmitter::parentNode(void) const
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
};

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerTransmitter *transmitter)
{
    debug.nospace() << transmitter->identifier();
    
    return debug.space();
};

