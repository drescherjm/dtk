/* @(#)dtkComposerGraphNodeSetInputs.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:38:36 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 45
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetInputs.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetInputsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetInputs::dtkComposerGraphNodeSetInputs(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetInputsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}



void dtkComposerGraphNodeSetInputs::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setInputs();
}


