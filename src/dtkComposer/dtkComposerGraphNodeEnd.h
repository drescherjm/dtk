/* @(#)dtkComposerGraphNodeEnd.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:33:35 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 32
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
class dtkComposerGraphNodeEndPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeEnd
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeEnd : public dtkComposerGraphNode
{
public:
    dtkComposerGraphNodeEnd(dtkComposerNode *node, const QString& title = "End");

public:
    void eval(void);

private:
    dtkComposerGraphNodeEndPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODEEND_H */

