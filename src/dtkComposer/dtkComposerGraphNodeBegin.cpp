/* @(#)dtkComposerGraphNodeBegin.cpp ---
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


#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeBeginPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeBegin::dtkComposerGraphNodeBegin(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeBeginPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeBegin::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->begin();
}


