/* @(#)dtkComposerGraphNodeSetVariables.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr. 14 16:56:51 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetVariables.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetVariablesPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetVariables::dtkComposerGraphNodeSetVariables(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetVariablesPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeSetVariables::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setVariables();
}


