/* @(#)dtkComposerGraphNodeSetOutputs.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:46:50 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetOutputs.h"

class dtkComposerGraphNodeSetOutputsPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeSetOutputs::dtkComposerGraphNodeSetOutputs(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetOutputsPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeSetOutputs::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->setOutputs();
}


