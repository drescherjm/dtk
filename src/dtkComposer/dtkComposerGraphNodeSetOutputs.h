/* @(#)dtkComposerGraphNodeSetOutputs.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:32:24 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETOUTPUTS_H
#define DTKCOMPOSERGRAPHNODESETOUTPUTS_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeSetOutputsPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetOutputs
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetOutputs : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSetOutputs(dtkComposerNode *node, const QString &title = "Set Outputs");

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetOutputsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETOUTPUTS_H */

