/* @(#)dtkComposerGraphNodeSetVariables.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:39:09 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 44
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetVariables.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetVariablesPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetVariables::dtkComposerGraphNodeSetVariables(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetVariablesPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}



void dtkComposerGraphNodeSetVariables::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setVariables();
}


