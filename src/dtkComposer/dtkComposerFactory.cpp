/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Sat Feb 25 00:28:21 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 83
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
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QMap<QString, QString> primitives;
    QMap<QString, QString> controls;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->primitives.insert("Boolean", "boolean");
    d->primitives.insert("Boolean Operator", "boolean operator");

    d->controls.insert("If", "if");
    d->controls.insert("For", "for");
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

    if(type == "if")
        return new dtkComposerNodeControlIf;

    if(type == "for")
        return new dtkComposerNodeControlFor;

    return NULL;
}

QMap<QString, QString> dtkComposerFactory::primitives(void)
{
    return d->primitives;
}

QMap<QString, QString> dtkComposerFactory::controls(void)
{
    return d->controls;
}
