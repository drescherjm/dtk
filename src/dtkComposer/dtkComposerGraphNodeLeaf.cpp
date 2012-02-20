/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:36:17 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 49
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


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeLeafPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeLeaf *>(cnode);
    this->setTitle(title);
}



void dtkComposerGraphNodeLeaf::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->run();
}


