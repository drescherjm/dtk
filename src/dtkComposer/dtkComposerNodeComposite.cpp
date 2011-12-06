/* dtkComposerNodeComposite.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Dec  6 14:01:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 14:06:37 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeComposite.h"

class dtkComposerNodeCompositePrivate
{
public:
};

dtkComposerNodeComposite::dtkComposerNodeComposite(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeCompositePrivate)
{
    static int count = 0;

    this->setKind(dtkComposerNode::Composite);
    this->setType("dtkComposerNodeComposite");
    this->setTitle(QString("Composite node %1").arg(++count));
}

dtkComposerNodeComposite::~dtkComposerNodeComposite(void)
{
    delete d;

    d = NULL;
}
