/* @(#)dtkComposerGraphNodeSetConditions.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:37:33 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETCONDITIONS_H
#define DTKCOMPOSERGRAPHNODESETCONDITIONS_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeSetConditionsPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetConditions
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetConditions : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSetConditions(dtkComposerNode *node, const QString& title = "Set Conditions");

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetConditionsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETCONDITIONS_H */

