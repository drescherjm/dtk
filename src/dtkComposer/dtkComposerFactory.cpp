/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Tue Feb 28 17:42:04 2012 (+0100)
 *           By: David Rey
 *     Update #: 237
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
#include "dtkComposerNodeConstants.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeList.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeVector.h"
#include "dtkComposerSceneNodeLeaf.h"

class dtkComposerFactoryPrivate
{
public:
    QMap<QString, QString> constants;
    QMap<QString, QString> primitives;
    QMap<QString, QString> containers;;
    QMap<QString, QString> operators;
    QMap<QString, QString> controls;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    d->constants.insert("Pi", "pi");
    d->constants.insert("E", "e");

    d->primitives.insert("Boolean", "boolean");
    d->primitives.insert("Integer", "integer");
    d->primitives.insert("Real", "real");
    d->primitives.insert("String", "string");
    
    d->containers.insert("List", "list");
    d->containers.insert("Vector", "vector");

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
    d->operators.insert("Eucldiv", "eucldiv");
    d->operators.insert("Expn", "expn");
    d->operators.insert("Logn", "logn");
    d->operators.insert("Minus", "minus");
    d->operators.insert("Modulo", "modulo");
    d->operators.insert("Mult", "mult");
    d->operators.insert("Plus", "plus");
    d->operators.insert("Posnthroot", "posnthroot");
    d->operators.insert("Power", "power");
    d->operators.insert("Ratio", "ratio");
    d->operators.insert("Equal", "equal");
    d->operators.insert("Notequal", "notequal");
    d->operators.insert("Gt", "gt");
    d->operators.insert("Lt", "lt");
    d->operators.insert("Gte", "gte");
    d->operators.insert("Lte", "lte");
    d->operators.insert("Almosteq", "almosteq");
    d->operators.insert("Notalmosteq", "notalmosteq");
    d->operators.insert("Not", "not");
    d->operators.insert("And", "and");
    d->operators.insert("Or", "or");
    d->operators.insert("Xor", "xor");
    d->operators.insert("Nand", "nand");
    d->operators.insert("Nor", "nor");
    d->operators.insert("Xnor", "xnor");
    d->operators.insert("Imp", "imp");
    d->operators.insert("Nimp", "nimp");

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

    if(type == "e")
        return new dtkComposerNodeE;

    // primitive nodes

    if(type == "boolean")
        return new dtkComposerNodeBoolean;

    if(type == "integer")
        return new dtkComposerNodeInteger;

    if(type == "real")
        return new dtkComposerNodeReal;

    if(type == "string")
        return new dtkComposerNodeString;

    // container nodes

    if(type == "list")
        return new dtkComposerNodeList;

    if(type == "vector")
        return new dtkComposerNodeVector;

    // operator nodes

    if(type == "not")
        return new dtkComposerNodeBooleanOperatorUnaryNot;

    if(type == "and")
        return new dtkComposerNodeBooleanOperatorBinaryAnd;

    if(type == "or")
        return new dtkComposerNodeBooleanOperatorBinaryOr;

    if(type == "xor")
        return new dtkComposerNodeBooleanOperatorBinaryXor;

    if(type == "nand")
        return new dtkComposerNodeBooleanOperatorBinaryNand;

    if(type == "nor")
        return new dtkComposerNodeBooleanOperatorBinaryNor;

    if(type == "xnor")
        return new dtkComposerNodeBooleanOperatorBinaryXnor;

    if(type == "imp")
        return new dtkComposerNodeBooleanOperatorBinaryImp;

    if(type == "nimp")
        return new dtkComposerNodeBooleanOperatorBinaryNimp;

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

    if (type =="eucldiv")
        return new dtkComposerNodeNumberOperatorBinaryEucldiv;

    if (type =="expn")
        return new dtkComposerNodeNumberOperatorBinaryExpn;

    if (type =="logn")
        return new dtkComposerNodeNumberOperatorBinaryLogn;

    if (type =="minus")
        return new dtkComposerNodeNumberOperatorBinaryMinus;

    if (type =="modulo")
        return new dtkComposerNodeNumberOperatorBinaryModulo;

    if (type =="mult")
        return new dtkComposerNodeNumberOperatorBinaryMult;

    if (type =="plus")
        return new dtkComposerNodeNumberOperatorBinaryPlus;

    if (type =="posnthroot")
        return new dtkComposerNodeNumberOperatorBinaryPosnthroot;

    if (type =="power")
        return new dtkComposerNodeNumberOperatorBinaryPower;

    if (type =="ratio")
        return new dtkComposerNodeNumberOperatorBinaryRatio;

    if (type =="equal")
        return new dtkComposerNodeNumberComparatorEqual;

    if (type =="notequal")
        return new dtkComposerNodeNumberComparatorNotequal;

    if (type =="gt")
        return new dtkComposerNodeNumberComparatorGt;

    if (type =="lt")
        return new dtkComposerNodeNumberComparatorLt;

    if (type =="gte")
        return new dtkComposerNodeNumberComparatorGte;

    if (type =="lte")
        return new dtkComposerNodeNumberComparatorLte;

    if (type =="almosteq")
        return new dtkComposerNodeNumberAlmosteq;

    if (type =="notalmosteq")
        return new dtkComposerNodeNumberNotalmosteq;

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

QMap<QString, QString> dtkComposerFactory::containers(void)
{
    return d->containers;
}

QMap<QString, QString> dtkComposerFactory::operators(void)
{
    return d->operators;
}

QMap<QString, QString> dtkComposerFactory::controls(void)
{
    return d->controls;
}
