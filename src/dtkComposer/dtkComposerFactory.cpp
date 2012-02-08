/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Wed Feb  8 16:02:53 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
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
    d->nodes.insert("Node", "leaf");
}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerSceneNode *dtkComposerFactory::create(const QString& type)
{
    if(type == "leaf")
        return new dtkComposerSceneNodeLeaf;

    return NULL;
}

QHash<QString, QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}
