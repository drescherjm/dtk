/* @(#)dtkComposerGraphNodeBegin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:24:04 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 41
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

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    dtkComposerNode *wrapee(void);

public:
    dtkComposerGraphNodeList successors(void);

public:
    void setEnd(dtkComposerGraphNode *end);

private:
    dtkComposerGraphNodeBeginPrivate *d;
};

