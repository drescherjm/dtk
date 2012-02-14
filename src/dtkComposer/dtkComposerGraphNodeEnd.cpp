/* @(#)dtkComposerGraphNodeEnd.cpp ---
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


#include "dtkComposerGraphNodeEnd.h"

class dtkComposerGraphNodeEndPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeEnd::dtkComposerGraphNodeEnd(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeEndPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeEnd::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->end();
}


