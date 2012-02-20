/* @(#)dtkComposerGraphNodeSetVariables.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:38:53 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 32
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETVARIABLES_H
#define DTKCOMPOSERGRAPHNODESETVARIABLES_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeSetVariablesPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetVariables
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetVariables : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSetVariables(dtkComposerNode *node, const QString& title = "Set Variables");

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetVariablesPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETVARIABLES_H */

