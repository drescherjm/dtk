/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr. 14 16:26:16 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 33
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeLeaf.h"

class dtkComposerGraphNodeLeafPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeLeafPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeLeaf::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->run();
}


