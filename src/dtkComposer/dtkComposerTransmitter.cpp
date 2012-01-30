/* dtkComposerTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:03:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 11:25:15 2012 (+0100)
 *           By: tkloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter.h"

#include <QtCore/QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerAbstractTransmitter::dtkComposerAbstractTransmitter(void) : d(new dtkComposerAbstractTransmitterPrivate)
{

}

dtkComposerAbstractTransmitter::~dtkComposerAbstractTransmitter(void)
{
    delete d;
    d = NULL;
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
