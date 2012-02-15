/* @(#)dtkComposerGraphNodeSetOutputs.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:11:17 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetOutputs.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetOutputsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetOutputs::dtkComposerGraphNodeSetOutputs(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetOutputsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeSetOutputs::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setOutputs();
}


