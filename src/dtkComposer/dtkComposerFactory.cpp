/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Mon Feb 27 16:16:27 2012 (+0100)
 *           By: David Rey
 *     Update #: 178
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
#include "dtkComposerNodeNumberOperator.h"
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
    d->operators.insert("Abs", "abs");
    d->operators.insert("Acos", "acos");
    d->operators.insert("Asin", "asin");
    d->operators.insert("Atan", "atan");
    d->operators.insert("Ceil", "ceil");
    d->operators.insert("Cos", "cos");
    d->operators.insert("Decr", "decr");
    d->operators.insert("Deg2Rad", "deg2rad");
    d->operators.insert("Exp", "exp");
    d->operators.insert("Floor", "floor");
    d->operators.insert("Incr", "incr");
    d->operators.insert("Inv", "inv");
    d->operators.insert("Ln", "ln");
    d->operators.insert("Log10", "log10");
    d->operators.insert("Opp", "opp");
    d->operators.insert("Round", "round");
    d->operators.insert("Rad2Deg", "rad2deg");
    d->operators.insert("Sin", "sin");
    d->operators.insert("Square", "square");
    d->operators.insert("Sqrt", "sqrt");
    d->operators.insert("Tan", "tan");

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

    if(type == "abs")
        return new dtkComposerNodeNumberOperatorUnaryAbs;

    if(type == "acos")
        return new dtkComposerNodeNumberOperatorUnaryAcos;

    if(type == "asin")
        return new dtkComposerNodeNumberOperatorUnaryAsin;

    if(type == "atan")
        return new dtkComposerNodeNumberOperatorUnaryAtan;

    if (type =="ceil")
        return new dtkComposerNodeNumberOperatorUnaryCeil;

    if (type =="cos")
        return new dtkComposerNodeNumberOperatorUnaryCos;

    if (type =="decr")
        return new dtkComposerNodeNumberOperatorUnaryDecr;

    if (type =="deg2rad")
        return new dtkComposerNodeNumberOperatorUnaryDeg2Rad;

    if (type =="exp")
        return new dtkComposerNodeNumberOperatorUnaryExp;

    if (type =="floor")
        return new dtkComposerNodeNumberOperatorUnaryFloor;

    if (type =="incr")
        return new dtkComposerNodeNumberOperatorUnaryIncr;

    if (type =="inv")
        return new dtkComposerNodeNumberOperatorUnaryInv;

    if (type =="ln")
        return new dtkComposerNodeNumberOperatorUnaryLn;

    if (type =="log10")
        return new dtkComposerNodeNumberOperatorUnaryLog10;

    if (type =="opp")
        return new dtkComposerNodeNumberOperatorUnaryOpp;

    if (type =="rad2deg")
        return new dtkComposerNodeNumberOperatorUnaryRad2Deg;

    if (type =="round")
        return new dtkComposerNodeNumberOperatorUnaryRound;

    if (type =="sin")
        return new dtkComposerNodeNumberOperatorUnarySin;

    if (type =="square")
        return new dtkComposerNodeNumberOperatorUnarySquare;

    if (type =="sqrt")
        return new dtkComposerNodeNumberOperatorUnarySqrt;

    if (type =="tan")
        return new dtkComposerNodeNumberOperatorUnaryTan;

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
