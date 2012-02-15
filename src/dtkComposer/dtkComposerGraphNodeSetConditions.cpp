/* @(#)dtkComposerGraphNodeSetConditions.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:10:06 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetConditions.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetConditionsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetConditions::dtkComposerGraphNodeSetConditions(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetConditionsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeSetConditions::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setConditions();
}


