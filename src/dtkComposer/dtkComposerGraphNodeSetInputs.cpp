/* @(#)dtkComposerGraphNodeSetInputs.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:39:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 32
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetInputs.h"

class dtkComposerGraphNodeSetInputsPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeSetInputs::dtkComposerGraphNodeSetInputs(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetInputsPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeSetInputs::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->setInputs();
}


