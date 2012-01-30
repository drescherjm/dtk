/* dtkComposerNode.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 14:56:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 16:51:48 2012 (+0100)
 *           By: tkloczko
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerAbstractTransmitter.h"

#include <dtkCore/dtkGlobal.h>

#include <QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    QList<dtkComposerAbstractTransmitter *> emitters;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNode implementation
// /////////////////////////////////////////////////////////////////

//! Constructs node.
/*! 
 *  
 */
dtkComposerNode::dtkComposerNode(void) : QObject(), d(new dtkComposerNodePrivate)
{

}

//! Destroys node.
/*! 
 *  
 */
dtkComposerNode::~dtkComposerNode(void)
{
    delete d;
    d = NULL;
}

//! Appends /a emitter in the list of emitters.
/*! 
 *  
 */
void dtkComposerNode::appendEmitter(dtkComposerAbstractTransmitter *emitter)
{
    if(!d->emitters.contains(emitter))
        d->emitters << emitter;
}

//! Removes /a emitter from the list of emitters.
/*! 
 *  
 */
void dtkComposerNode::removeEmitter(dtkComposerAbstractTransmitter *emitter)
{
    d->emitters.removeAll(emitter);
}

//! Removes emitter at position /a index from the list of emitters.
/*! 
 *  
 */
void dtkComposerNode::removeEmitter(int index)
{
    d->emitters.removeAt(index);
}

//! Returns emitter at position /a index.
/*! 
 *  
 */
dtkComposerAbstractTransmitter *dtkComposerNode::emitter(int index)
{
    return d->emitters.at(index);
}

//! Returns emitter at position /a index.
/*! 
 *  
 */
void dtkComposerNode::setReceiver(dtkComposerAbstractTransmitter *transmitter)
{
    DTK_UNUSED(transmitter);
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerNode& node)
{
    dbg.nospace() << node.identifier();
    
    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerNode *node)
{
    dbg.nospace() << node->identifier();
    
    return dbg.space();
}
