/* @(#)dtkComposerGraphNodeSetInputs.cpp ---
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


#include "dtkComposerGraphNodeSetInputs.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetInputsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetInputs::dtkComposerGraphNodeSetInputs(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetInputsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeSetInputs::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setInputs();
}


