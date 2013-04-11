/* @(#)dtkComposerGraphNodeLeaf.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:26:12 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 38
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

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


