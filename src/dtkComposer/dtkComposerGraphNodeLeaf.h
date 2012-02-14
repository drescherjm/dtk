/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mar. févr. 14 16:49:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 28
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODELEAF_H
#define DTKCOMPOSERGRAPHNODELEAF_H

#include "dtkComposerNode.h"
#include "dtkComposerGraphNode.h"

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

