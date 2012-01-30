/* dtkComposerNode.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 14:56:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 15:02:42 2012 (+0100)
 *           By: tkloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"

#include <QtCore/QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNode implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(void) : d(new dtkComposerNodePrivate)
{

}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;
    d = NULL;
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
