/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Tue Jan 31 15:56:07 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerFactory.h"
#include "dtkComposerScene_p.h"

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

    return new dtkComposerSceneNode;
}

QHash<QString, QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}
