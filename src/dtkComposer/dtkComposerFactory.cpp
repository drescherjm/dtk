/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Fri Feb  3 13:58:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerFactory.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QHash<QString, QString> nodes;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->nodes.insert("Node A", "typeA");
    d->nodes.insert("Node B", "typeB");
    d->nodes.insert("Node C", "typeC");
}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerSceneNode *dtkComposerFactory::create(const QString& type)
{
    Q_UNUSED(type);

    return new dtkComposerSceneNodeLeaf;
}

QHash<QString, QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}
