/* dtkComposerNodeTransmitter.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 11:04:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov  2 11:12:16 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeTransmitter.h"

#include <QtCore/QDebug>

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

//! Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter)
{
    debug.nospace() << transmitter.identifier();
    
    return debug.space();
};

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerNodeAbstractTransmitter *transmitter)
{
    debug.nospace() << transmitter->identifier();
    
    return debug.space();
};
