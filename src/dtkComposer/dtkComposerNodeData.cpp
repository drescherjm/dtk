/* dtkComposerNodeData.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:21:51 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 16:21:05 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeData.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeDataPrivate
{
public:
};

dtkComposerNodeData::dtkComposerNodeData(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeDataPrivate)
{
    this->setKind(dtkComposerNode::Data);
}

dtkComposerNodeData::~dtkComposerNodeData(void)
{
    if (this->object())
        delete this->object();

    delete d;

    d = NULL;
}

void dtkComposerNodeData::run(void)
{
    return;
}
