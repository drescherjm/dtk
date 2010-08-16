/* dtkComposerNodeData.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:21:51 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 16:16:53 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeData.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeDataPrivate
{
public:
};

dtkComposerNodeData::dtkComposerNodeData(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeDataPrivate)
{
    this->setKind(dtkComposerNode::Data);
    // this->addInputProperty(new dtkComposerNodeProperty("if", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this));
    // this->addOutputProperty(new dtkComposerNodeProperty("then", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this));
    // this->addOutputProperty(new dtkComposerNodeProperty("else", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this));
}

dtkComposerNodeData::~dtkComposerNodeData(void)
{
    delete d;

    d = NULL;
}
