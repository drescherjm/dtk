/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: lun. févr. 27 15:35:35 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 148
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
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodePi.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QMap<QString, QString> constants;
    QMap<QString, QString> primitives;
    QMap<QString, QString> operators;
    QMap<QString, QString> controls;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->constants.insert("Pi", "pi");

    d->primitives.insert("Boolean", "boolean");
    d->primitives.insert("Integer", "integer");
    d->primitives.insert("Real", "real");
    d->primitives.insert("String", "string");

    d->operators.insert("Boolean Operator", "boolean operator");

    d->controls.insert("Do While", "do while");
    d->controls.insert("If", "if");
    d->controls.insert("For", "for");
    d->controls.insert("For Each", "foreach");
    d->controls.insert("While", "while");
}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerFactory::create(const QString& type)
{
    // constant nodes

    if(type == "pi")
        return new dtkComposerNodePi;

    // primitive nodes

    if(type == "boolean")
        return new dtkComposerNodeBoolean;

    if(type == "integer")
        return new dtkComposerNodeInteger;

    if(type == "real")
        return new dtkComposerNodeReal;

    if(type == "string")
        return new dtkComposerNodeString;

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

    if(type == "foreach")
        return new dtkComposerNodeControlForEach;

    if(type == "while")
        return new dtkComposerNodeControlWhile;

    return NULL;
}

QMap<QString, QString> dtkComposerFactory::constants(void)
{
    return d->constants;
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
