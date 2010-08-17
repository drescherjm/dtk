/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 12 11:26:22 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 16:18:26 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeString.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeStringPrivate
{
public:
    QString string;
};

dtkComposerNodeString::dtkComposerNodeString(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringPrivate)
{
    this->setTitle("String");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerString");
    this->addInputProperty(new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this));
    this->addOutputProperty(new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this));
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}
