/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 09:55:06 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 29
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
#include "dtkComposerNode.h"

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

