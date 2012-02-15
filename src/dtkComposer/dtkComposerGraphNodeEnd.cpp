/* @(#)dtkComposerGraphNodeEnd.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:08:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeEnd.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeEndPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeEnd::dtkComposerGraphNodeEnd(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeEndPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeEnd::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->end();
}


