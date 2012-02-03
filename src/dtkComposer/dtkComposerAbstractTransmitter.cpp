/* dtkComposerAbstractTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 14:12:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerAbstractTransmitter.h"
#include "dtkComposerSceneNode.h"

#include <QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate
{
public:
    dtkComposerSceneNode *parent;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerAbstractTransmitter::dtkComposerAbstractTransmitter(dtkComposerSceneNode *parent) : d(new dtkComposerAbstractTransmitterPrivate)
{
    d->parent = parent;
}

dtkComposerAbstractTransmitter::~dtkComposerAbstractTransmitter(void)
{
    delete d;

    d = NULL;
}

dtkComposerSceneNode *dtkComposerAbstractTransmitter::parentNode(void) const
{
    return d->parent;
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

//! Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, const dtkComposerAbstractTransmitter& transmitter)
{
    debug.nospace() << transmitter.identifier();
    
    return debug.space();
};

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerAbstractTransmitter *transmitter)
{
    debug.nospace() << transmitter->identifier();
    
    return debug.space();
};

