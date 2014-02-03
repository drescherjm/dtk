/* @(#)dtkComposerGraphNodeEnd.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mar. janv. 29 16:26:01 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 43
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODEEND_H
#define DTKCOMPOSERGRAPHNODEEND_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeBegin;
class dtkComposerGraphNodeEndPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeEnd
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeEnd : public dtkComposerGraphNode
{
public:
    dtkComposerGraphNodeEnd(dtkComposerNode *node, const QString& title = "End");

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    void eval(void);

public:
    dtkComposerNode *wrapee(void);

public:
    dtkComposerGraphNodeList predecessors(void);

public:
    void setBegin(dtkComposerGraphNodeBegin *begin);

private:
    dtkComposerGraphNodeEndPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODEEND_H */

