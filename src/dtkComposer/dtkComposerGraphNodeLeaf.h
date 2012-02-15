/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:08:11 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 31
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
     dtkComposerGraphNodeLeaf(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeLeafPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODELEAF_H */

