/* dtkComposerAbstractTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 16:51:07 2012 (+0100)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerAbstractTransmitter.h"
#include "dtkComposerNode.h"

#include <QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate
{
public:
    dtkComposerNode *parent;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerAbstractTransmitter::dtkComposerAbstractTransmitter(dtkComposerNode *parent) : QObject(parent), d(new dtkComposerAbstractTransmitterPrivate)
{
    d->parent = parent;
}

dtkComposerAbstractTransmitter::~dtkComposerAbstractTransmitter(void)
{
    delete d;
    d = NULL;
}

dtkComposerNode *dtkComposerAbstractTransmitter::parentNode(void) const
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

