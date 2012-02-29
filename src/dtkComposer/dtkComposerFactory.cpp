/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: Wed Feb 29 02:41:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 387
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

#include <dtkCore/dtkGlobal.h>

class dtkComposerFactoryPrivate
{
public:
    QList<QString> nodes;
    QHash<QString, QString> descriptions;
    QHash<QString, QStringList> tags;
    QHash<QString, QString> types;
};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{
    // constant nodes

    d->nodes << "Pi";
    d->descriptions["Pi"] = dtkReadFile(":dtkComposer/dtkComposerNodePi.html");
    d->tags["Pi"] = QStringList() << "constant" << "pi";
    d->types["Pi"] = "pi";

    d->nodes << "E";
    d->descriptions["E"] = dtkReadFile(":dtkComposer/dtkComposerNodeE.html");
    d->tags["E"] = QStringList() << "constant" << "e";
    d->types["E"] = "e";

    // primitive nodes

    d->nodes << "Boolean";
    d->descriptions["Boolean"] = "Not filled yet";
    d->tags["Boolean"] = QStringList() << "primitive" << "boolean";
    d->types["Boolean"] = "boolean";

    d->nodes << "Integer";
    d->descriptions["Integer"] = "Not filled yet";
    d->tags["Integer"] = QStringList() << "primitive" << "integer" << "number";
    d->types["Integer"] = "integer";

    d->nodes << "Real";
    d->descriptions["Real"] = "Not filled yet";
    d->tags["Real"] = QStringList() << "primitive" << "real" << "number";
    d->types["Real"] = "real";

    d->nodes << "String";
    d->descriptions["String"] = "Not filled yet";
    d->tags["String"] = QStringList() << "primitive" << "string";
    d->types["String"] = "string";
    
    // container nodes

    d->nodes << "List";
    d->descriptions["List"] = "Not filled yet";
    d->tags["List"] = QStringList() << "container" << "list";
    d->types["List"] = "list";

    d->nodes << "Vector";
    d->descriptions["Vector"] = "Not filled yet";
    d->tags["Vector"] = QStringList() << "container" << "vector";
    d->types["Vector"] = "vector";

    // operators

    d->nodes << "Abs";
    d->descriptions["Abs"] = "Not filled yet";
    d->tags["Abs"] = QStringList() << "number" << "operator" << "unary" << "abs";
    d->types["Abs"] = "abs";

    d->nodes << "Acos";
    d->descriptions["Acos"] = "Not filled yet";
    d->tags["Acos"] = QStringList() << "number" << "operator" << "unary" << "acos";
    d->types["Acos"] = "acos";

    d->nodes << "Asin";
    d->descriptions["Asin"] = "Not filled yet";
    d->tags["Asin"] = QStringList() << "number" << "operator" << "unary" << "asin";
    d->types["Asin"] = "asin";

    d->nodes << "Atan";
    d->descriptions["Atan"] = "Not filled yet";
    d->tags["Atan"] = QStringList() << "number" << "operator" << "unary" << "atan";
    d->types["Atan"] = "atan";

    d->nodes << "Ceil";
    d->descriptions["Ceil"] = "Not filled yet";
    d->tags["Ceil"] = QStringList() << "number" << "operator" << "unary" << "ceil";
    d->types["Ceil"] = "ceil";

    d->nodes << "Cos";
    d->descriptions["Cos"] = "Not filled yet";
    d->tags["Cos"] = QStringList() << "number" << "operator" << "unary" << "cos";
    d->types["Cos"] = "cos";

    d->nodes << "Decr";
    d->descriptions["Decr"] = "Not filled yet";
    d->tags["Decr"] = QStringList() << "number" << "operator" << "unary" << "decr";
    d->types["Decr"] = "decr";

    d->nodes << "Deg2rad";
    d->descriptions["Deg2rad"] = "Not filled yet";
    d->tags["Deg2rad"] = QStringList() << "number" << "operator" << "unary" << "deg2rad";
    d->types["Deg2rad"] = "deg2rad";

    d->nodes << "Exp";
    d->descriptions["Exp"] = "Not filled yet";
    d->tags["Exp"] = QStringList() << "number" << "operator" << "unary" << "exp";
    d->types["Exp"] = "exp";

    d->nodes << "Floor";
    d->descriptions["Floor"] = "Not filled yet";
    d->tags["Floor"] = QStringList() << "number" << "operator" << "unary" << "floor";
    d->types["Floor"] = "floor";

    d->nodes << "Incr";
    d->descriptions["Incr"] = "Not filled yet";
    d->tags["Incr"] = QStringList() << "number" << "operator" << "unary" << "incr";
    d->types["Incr"] = "incr";

    d->nodes << "Inv";
    d->descriptions["Inv"] = "Not filled yet";
    d->tags["Inv"] = QStringList() << "number" << "operator" << "unary" << "inv";
    d->types["Inv"] = "inv";

    d->nodes << "Ln";
    d->descriptions["Ln"] = "Not filled yet";
    d->tags["Ln"] = QStringList() << "number" << "operator" << "unary" << "ln";
    d->types["Ln"] = "ln";

    d->nodes << "Log10";
    d->descriptions["Log10"] = "Not filled yet";
    d->tags["Log10"] = QStringList() << "number" << "operator" << "unary" << "log10";
    d->types["Log10"] = "log10";

    d->nodes << "Opp";
    d->descriptions["Opp"] = "Not filled yet";
    d->tags["Opp"] = QStringList() << "number" << "operator" << "unary" << "opp";
    d->types["Opp"] = "opp";

    d->nodes << "Round";
    d->descriptions["Round"] = "Not filled yet";
    d->tags["Round"] = QStringList() << "number" << "operator" << "unary" << "round";
    d->types["Round"] = "round";

    d->nodes << "Rad2deg";
    d->descriptions["Rad2deg"] = "Not filled yet";
    d->tags["Rad2deg"] = QStringList() << "number" << "operator" << "unary" << "rad2deg";
    d->types["Rad2deg"] = "rad2deg";

    d->nodes << "Sin";
    d->descriptions["Sin"] = "Not filled yet";
    d->tags["Sin"] = QStringList() << "number" << "operator" << "unary" << "sin";
    d->types["Sin"] = "sin";

    d->nodes << "Square";
    d->descriptions["Square"] = "Not filled yet";
    d->tags["Square"] = QStringList() << "number" << "operator" << "unary" << "square";
    d->types["Square"] = "square";

    d->nodes << "Sqrt";
    d->descriptions["Sqrt"] = "Not filled yet";
    d->tags["Sqrt"] = QStringList() << "number" << "operator" << "unary" << "sqrt";
    d->types["Sqrt"] = "sqrt";

    d->nodes << "Tan";
    d->descriptions["Tan"] = "Not filled yet";
    d->tags["Tan"] = QStringList() << "number" << "operator" << "unary" << "tan";
    d->types["Tan"] = "tan";

    d->nodes << "Eucldiv";
    d->descriptions["Eucldiv"] = "Not filled yet";
    d->tags["Eucldiv"] = QStringList() << "number" << "operator" << "binary" << "eucldiv";
    d->types["Eucldiv"] = "eucldiv";

    d->nodes << "Expn";
    d->descriptions["Expn"] = "Not filled yet";
    d->tags["Expn"] = QStringList() << "number" << "operator" << "binary" << "expn";
    d->types["Expn"] = "expn";

    d->nodes << "Logn";
    d->descriptions["Logn"] = "Not filled yet";
    d->tags["Logn"] = QStringList() << "number" << "operator" << "binary" << "logn";
    d->types["Logn"] = "logn";

    d->nodes << "Minus";
    d->descriptions["Minus"] = "Not filled yet";
    d->tags["Minus"] = QStringList() << "number" << "operator" << "binary" << "minus";
    d->types["Minus"] = "minus";

    d->nodes << "Modulo";
    d->descriptions["Modulo"] = "Not filled yet";
    d->tags["Modulo"] = QStringList() << "number" << "operator" << "binary" << "modulo";
    d->types["Modulo"] = "modulo";

    d->nodes << "Mult";
    d->descriptions["Mult"] = "Not filled yet";
    d->tags["Mult"] = QStringList() << "number" << "operator" << "binary" << "mult";
    d->types["Mult"] = "mult";

    d->nodes << "Plus";
    d->descriptions["Plus"] = "Not filled yet";
    d->tags["Plus"] = QStringList() << "number" << "operator" << "binary" << "plus";
    d->types["Plus"] = "plus";

    d->nodes << "Posnthroot";
    d->descriptions["Posnthroot"] = "Not filled yet";
    d->tags["Posnthroot"] = QStringList() << "number" << "operator" << "binary" << "posnthroot";
    d->types["Posnthroot"] = "posnthroot";

    d->nodes << "Power";
    d->descriptions["Power"] = "Not filled yet";
    d->tags["Power"] = QStringList() << "number" << "operator" << "binary" << "power";
    d->types["Power"] = "power";

    d->nodes << "Ratio";
    d->descriptions["Ratio"] = "Not filled yet";
    d->tags["Ratio"] = QStringList() << "number" << "operator" << "binary" << "ratio";
    d->types["Ratio"] = "ratio";

    d->nodes << "Equal";
    d->descriptions["Equal"] = "Not filled yet";
    d->tags["Equal"] = QStringList() << "number" << "operator" << "binary" << "equal";
    d->types["Equal"] = "equal";

    d->nodes << "Notequal";
    d->descriptions["Notequal"] = "Not filled yet";
    d->tags["Notequal"] = QStringList() << "number" << "operator" << "binary" << "notequal";
    d->types["Notequal"] = "notequal";

    d->nodes << "Gt";
    d->descriptions["Gt"] = "Not filled yet";
    d->tags["Gt"] = QStringList() << "number" << "operator" << "binary" << "gt";
    d->types["Gt"] = "gt";

    d->nodes << "Lt";
    d->descriptions["Lt"] = "Not filled yet";
    d->tags["Lt"] = QStringList() << "number" << "operator" << "binary" << "lt";
    d->types["Lt"] = "lt";

    d->nodes << "Gte";
    d->descriptions["Gte"] = "Not filled yet";
    d->tags["Gte"] = QStringList() << "number" << "operator" << "binary" << "gte";
    d->types["Gte"] = "gte";

    d->nodes << "Lte";
    d->descriptions["Lte"] = "Not filled yet";
    d->tags["Lte"] = QStringList() << "number" << "operator" << "binary" << "lte";
    d->types["Lte"] = "lte";

    d->nodes << "Almosteq";
    d->descriptions["Almosteq"] = "Not filled yet";
    d->tags["Almosteq"] = QStringList() << "number" << "operator" << "binary" << "almosteq";
    d->types["Almosteq"] = "almosteq";

    d->nodes << "Notalmosteq";
    d->descriptions["Notalmosteq"] = "Not filled yet";
    d->tags["Notalmosteq"] = QStringList() << "number" << "operator" << "binary" << "notalmosteq";
    d->types["Notalmosteq"] = "notalmosteq";

// /////////////////////////////////////////////////////////////////

    d->nodes << "Not";
    d->descriptions["Not"] = "Not filled yet";
    d->tags["Not"] = QStringList() << "boolean" << "operator" << "unary" << "not";
    d->types["Not"] = "not";

    d->nodes << "And";
    d->descriptions["And"] = "Not filled yet";
    d->tags["And"] = QStringList() << "boolean" << "operator" << "binary" << "and";
    d->types["And"] = "and";

    d->nodes << "Or";
    d->descriptions["Or"] = "Not filled yet";
    d->tags["Or"] = QStringList() << "boolean" << "operator" << "binary" << "or";
    d->types["Or"] = "or";

    d->nodes << "Xor";
    d->descriptions["Xor"] = "Not filled yet";
    d->tags["Xor"] = QStringList() << "boolean" << "operator" << "binary" << "xor";
    d->types["Xor"] = "xor";

    d->nodes << "Nand";
    d->descriptions["Nand"] = "Not filled yet";
    d->tags["Nand"] = QStringList() << "boolean" << "operator" << "binary" << "nand";
    d->types["Nand"] = "nand";

    d->nodes << "Nor";
    d->descriptions["Nor"] = "Not filled yet";
    d->tags["Nor"] = QStringList() << "boolean" << "operator" << "binary" << "nor";
    d->types["Nor"] = "nor";

    d->nodes << "Xnor";
    d->descriptions["Xnor"] = "Not filled yet";
    d->tags["Xnor"] = QStringList() << "boolean" << "operator" << "binary" << "xnor";
    d->types["Xnor"] = "xnor";

    d->nodes << "Imp";
    d->descriptions["Imp"] = "Not filled yet";
    d->tags["Imp"] = QStringList() << "boolean" << "operator" << "binary" << "imp";
    d->types["Imp"] = "imp";

    d->nodes << "Nimp";
    d->descriptions["Nimp"] = "Not filled yet";
    d->tags["Nimp"] = QStringList() << "boolean" << "operator" << "binary" << "nimp";
    d->types["Nimp"] = "nimp";

    // control nodes

    d->nodes << "Do While";
    d->descriptions["Do While"] = "Not filled yet";
    d->tags["Do While"] = QStringList() << "control" << "do" << "while";
    d->types["Do While"] = "do while";

    d->nodes << "If";
    d->descriptions["If"] = "Not filled yet";
    d->tags["If"] = QStringList() << "control" << "if";
    d->types["If"] = "if";

    d->nodes << "For";
    d->descriptions["For"] = "Not filled yet";
    d->tags["For"] = QStringList() << "control" << "for";
    d->types["For"] = "for";

    d->nodes << "Foreach";
    d->descriptions["Foreach"] = "Not filled yet";
    d->tags["Foreach"] = QStringList() << "control" << "foreach";
    d->types["Foreach"] = "foreach";

    d->nodes << "While";
    d->descriptions["While"] = "Not filled yet";
    d->tags["While"] = QStringList() << "control" << "while";
    d->types["While"] = "while";
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

QList<QString> dtkComposerFactory::nodes(void)
{
    return d->nodes;
}

QHash<QString, QString> dtkComposerFactory::descriptions(void)
{
    return d->descriptions;
}

QHash<QString, QStringList> dtkComposerFactory::tags(void)
{
    return d->tags;
}

QHash<QString, QString> dtkComposerFactory::types(void)
{
    return d->types;
}
