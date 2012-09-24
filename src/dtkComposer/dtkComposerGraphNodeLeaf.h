/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: jeu. sept. 20 22:05:33 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 37
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

public slots:
    void eval(void);

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeLeafPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODELEAF_H */

