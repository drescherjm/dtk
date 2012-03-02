/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:36:50 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODELEAF_H
#define DTKCOMPOSERGRAPHNODELEAF_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeLeafPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeLeaf
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeLeaf : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeLeaf(dtkComposerNode *node, const QString& title = "Leaf");

public:
    void eval(void);

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeLeafPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODELEAF_H */

