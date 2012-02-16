/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Thu Feb 16 12:45:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerFactory.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeFor.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QHash<QString, QString> nodes;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->nodes.insert("Boolean", "boolean");
    d->nodes.insert("Boolean Operator", "boolean operator");

// --
    d->nodes.insert("For", "for");
// --
}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerFactory::create(const QString& type)
{
    if(type == "boolean")
        return new dtkComposerNodeBoolean;

    if(type == "boolean operator")
        return new dtkComposerNodeBooleanOperator;

// --
    if(type == "for")
        return new dtkComposerNodeFor;
// --

    return NULL;
}

QHash<QString, QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}
