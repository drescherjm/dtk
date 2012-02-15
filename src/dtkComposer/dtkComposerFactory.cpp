/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Wed Feb 15 11:05:50 2012 (+0100)
 *           By: tkloczko
 *     Update #: 44
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

    return NULL;
}

QHash<QString, QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}
