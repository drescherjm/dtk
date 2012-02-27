/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:46:32 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 131
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
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QMap<QString, QString> primitives;
    QMap<QString, QString> operators;
    QMap<QString, QString> controls;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->primitives.insert("Boolean", "boolean");
    d->primitives.insert("Integer", "integer");
    d->primitives.insert("Real", "real");

    d->operators.insert("Boolean Operator", "boolean operator");

    d->controls.insert("Do While", "do while");
    d->controls.insert("If", "if");
    d->controls.insert("For", "for");
    d->controls.insert("While", "while");
}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerFactory::create(const QString& type)
{
    // primitive nodes

    if(type == "boolean")
        return new dtkComposerNodeBoolean;

    if(type == "integer")
        return new dtkComposerNodeInteger;

    if(type == "real")
        return new dtkComposerNodeReal;

    // operator nodes

    if(type == "boolean operator")
        return new dtkComposerNodeBooleanOperator;

    // control nodes

    if(type == "do while")
        return new dtkComposerNodeControlDoWhile;

    if(type == "if")
        return new dtkComposerNodeControlIf;

    if(type == "for")
        return new dtkComposerNodeControlFor;

    if(type == "while")
        return new dtkComposerNodeControlWhile;

    return NULL;
}

QMap<QString, QString> dtkComposerFactory::primitives(void)
{
    return d->primitives;
}

QMap<QString, QString> dtkComposerFactory::operators(void)
{
    return d->operators;
}

QMap<QString, QString> dtkComposerFactory::controls(void)
{
    return d->controls;
}
