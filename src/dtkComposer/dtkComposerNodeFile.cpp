/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:28:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul 13 10:24:36 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeFilePrivate
{
public:
    QString file;
};

dtkComposerNodeFile::dtkComposerNodeFile(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeFilePrivate)
{
    this->setTitle("File");
    this->setType(dtkComposerNode::Atomic);
    this->addInputProperty(new dtkComposerNodeProperty("path", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this));
    this->addOutputProperty(new dtkComposerNodeProperty("name", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this));
    this->addOutputProperty(new dtkComposerNodeProperty("text", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this));
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;

    d = NULL;
}
