/* @(#)dtkComposerGraphNodeBegin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: ven. sept. 20 09:11:37 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 67
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODEBEGIN_H
#define DTKCOMPOSERGRAPHNODEBEGIN_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeBeginPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeBegin
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeBegin : public dtkComposerGraphNode
{
public:
    dtkComposerGraphNodeBegin(dtkComposerNode *node, const QString& title = "Begin");

public:
    void eval(void);

public:
    dtkComposerGraphNode::Kind kind(void);

    void setKind(dtkComposerGraphNode::Kind);

public:
    dtkComposerNode *wrapee(void);

public:
    dtkComposerGraphNodeList successors(void);

public:
    dtkComposerGraphNodeList evaluableChilds(void);

public:
    dtkComposerGraphNode *end(void);
    void setEnd(dtkComposerGraphNode *end);

private:
    dtkComposerGraphNodeBeginPrivate *d;
};


#endif /* DTKCOMPOSERGRAPHNODEBEGIN_H */

