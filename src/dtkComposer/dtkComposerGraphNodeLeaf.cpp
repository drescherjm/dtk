/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:08:21 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 46
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeLeaf.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerGraphNodeLeafPrivate
{
public:
    dtkComposerNodeLeaf *composer_node;

};


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeLeafPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeLeaf *>(cnode);
}



void dtkComposerGraphNodeLeaf::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->run();
}


