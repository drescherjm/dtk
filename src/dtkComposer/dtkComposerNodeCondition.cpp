/* dtkComposerNodeCondition.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 12 13:51:53 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 16:14:49 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeCondition.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeConditionPrivate
{
public:
    QString condition;
};

dtkComposerNodeCondition::dtkComposerNodeCondition(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeConditionPrivate)
{
    this->setTitle("Condition");
    this->setKind(dtkComposerNode::Control);
    this->setType("dtkComposerConditon");
    this->addInputProperty(new dtkComposerNodeProperty("if", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this));
    this->addOutputProperty(new dtkComposerNodeProperty("then", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this));
    this->addOutputProperty(new dtkComposerNodeProperty("else", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this));
}

dtkComposerNodeCondition::~dtkComposerNodeCondition(void)
{
    delete d;

    d = NULL;
}
