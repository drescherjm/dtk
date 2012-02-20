/* @(#)dtkComposerGraphNodeBegin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:34:33 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 34
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

private:
    dtkComposerGraphNodeBeginPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODEBEGIN_H */

