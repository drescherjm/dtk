/* @(#)dtkComposerGraphNodeSetConditions.cpp ---
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


#include "dtkComposerGraphNodeSetConditions.h"

class dtkComposerGraphNodeSetConditionsPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeSetConditions::dtkComposerGraphNodeSetConditions(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetConditionsPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeSetConditions::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->setConditions();
}


