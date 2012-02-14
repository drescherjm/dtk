/* @(#)dtkComposerGraphNodeBegin.cpp ---
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


#include "dtkComposerGraphNodeBegin.h"

class dtkComposerGraphNodeBeginPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeBegin::dtkComposerGraphNodeBegin(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeBeginPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeBegin::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->begin();
}


