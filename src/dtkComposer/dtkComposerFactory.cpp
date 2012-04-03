/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: mar. avril  3 15:36:11 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 487
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
#include "dtkComposerNodeDistributed.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeFileOperator.h"
#include "dtkComposerNodeList.h"
#include "dtkComposerNodeLogger.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeVector.h"
#include "dtkComposerNodeWorld.h"
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
    d->descriptions["Boolean"] = "<p>Description not yet filled!</p>";
    d->tags["Boolean"] = QStringList() << "primitive" << "boolean";
    d->types["Boolean"] = "boolean";

    d->nodes << "Integer";
    d->descriptions["Integer"] = "<p>Description not yet filled!</p>";
    d->tags["Integer"] = QStringList() << "primitive" << "integer" << "number";
    d->types["Integer"] = "integer";

    d->nodes << "Real";
    d->descriptions["Real"] = "<p>Description not yet filled!</p>";
    d->tags["Real"] = QStringList() << "primitive" << "real" << "number";
    d->types["Real"] = "real";

    d->nodes << "String";
    d->descriptions["String"] = "<p>Description not yet filled!</p>";
    d->tags["String"] = QStringList() << "primitive" << "string";
    d->types["String"] = "string";

    d->nodes << "File";
    d->descriptions["File"] = "<p>Description not yet filled!</p>";
    d->tags["File"] = QStringList() << "primitive" << "file";
    d->types["File"] = "file";
    
    // container nodes

    d->nodes << "List";
    d->descriptions["List"] = "<p>Description not yet filled!</p>";
    d->tags["List"] = QStringList() << "container" << "list";
    d->types["List"] = "list";

    d->nodes << "Vector";
    d->descriptions["Vector"] = "<p>Description not yet filled!</p>";
    d->tags["Vector"] = QStringList() << "container" << "vector";
    d->types["Vector"] = "vector";

    // operators

    d->nodes << "Abs";
    d->descriptions["Abs"] = "<p>Description not yet filled!</p>";
    d->tags["Abs"] = QStringList() << "number" << "operator" << "unary" << "abs";
    d->types["Abs"] = "abs";

    d->nodes << "Acos";
    d->descriptions["Acos"] = "<p>Description not yet filled!</p>";
    d->tags["Acos"] = QStringList() << "number" << "operator" << "unary" << "acos";
    d->types["Acos"] = "acos";

    d->nodes << "Asin";
    d->descriptions["Asin"] = "<p>Description not yet filled!</p>";
    d->tags["Asin"] = QStringList() << "number" << "operator" << "unary" << "asin";
    d->types["Asin"] = "asin";

    d->nodes << "Atan";
    d->descriptions["Atan"] = "<p>Description not yet filled!</p>";
    d->tags["Atan"] = QStringList() << "number" << "operator" << "unary" << "atan";
    d->types["Atan"] = "atan";

    d->nodes << "Ceil";
    d->descriptions["Ceil"] = "<p>Description not yet filled!</p>";
    d->tags["Ceil"] = QStringList() << "number" << "operator" << "unary" << "ceil";
    d->types["Ceil"] = "ceil";

    d->nodes << "Cos";
    d->descriptions["Cos"] = "<p>Description not yet filled!</p>";
    d->tags["Cos"] = QStringList() << "number" << "operator" << "unary" << "cos";
    d->types["Cos"] = "cos";

    d->nodes << "Decr";
    d->descriptions["Decr"] = "<p>Description not yet filled!</p>";
    d->tags["Decr"] = QStringList() << "number" << "operator" << "unary" << "decr";
    d->types["Decr"] = "decr";

    d->nodes << "Deg2rad";
    d->descriptions["Deg2rad"] = "<p>Description not yet filled!</p>";
    d->tags["Deg2rad"] = QStringList() << "number" << "operator" << "unary" << "deg2rad";
    d->types["Deg2rad"] = "deg2rad";

    d->nodes << "Exp";
    d->descriptions["Exp"] = "<p>Description not yet filled!</p>";
    d->tags["Exp"] = QStringList() << "number" << "operator" << "unary" << "exp";
    d->types["Exp"] = "exp";

    d->nodes << "Floor";
    d->descriptions["Floor"] = "<p>Description not yet filled!</p>";
    d->tags["Floor"] = QStringList() << "number" << "operator" << "unary" << "floor";
    d->types["Floor"] = "floor";

    d->nodes << "Incr";
    d->descriptions["Incr"] = "<p>Description not yet filled!</p>";
    d->tags["Incr"] = QStringList() << "number" << "operator" << "unary" << "incr";
    d->types["Incr"] = "incr";

    d->nodes << "Inv";
    d->descriptions["Inv"] = "<p>Description not yet filled!</p>";
    d->tags["Inv"] = QStringList() << "number" << "operator" << "unary" << "inv";
    d->types["Inv"] = "inv";

    d->nodes << "Ln";
    d->descriptions["Ln"] = "<p>Description not yet filled!</p>";
    d->tags["Ln"] = QStringList() << "number" << "operator" << "unary" << "ln";
    d->types["Ln"] = "ln";

    d->nodes << "Log10";
    d->descriptions["Log10"] = "<p>Description not yet filled!</p>";
    d->tags["Log10"] = QStringList() << "number" << "operator" << "unary" << "log10";
    d->types["Log10"] = "log10";

    d->nodes << "Opp";
    d->descriptions["Opp"] = "<p>Description not yet filled!</p>";
    d->tags["Opp"] = QStringList() << "number" << "operator" << "unary" << "opp";
    d->types["Opp"] = "opp";

    d->nodes << "Round";
    d->descriptions["Round"] = "<p>Description not yet filled!</p>";
    d->tags["Round"] = QStringList() << "number" << "operator" << "unary" << "round";
    d->types["Round"] = "round";

    d->nodes << "Rad2deg";
    d->descriptions["Rad2deg"] = "<p>Description not yet filled!</p>";
    d->tags["Rad2deg"] = QStringList() << "number" << "operator" << "unary" << "rad2deg";
    d->types["Rad2deg"] = "rad2deg";

    d->nodes << "Sin";
    d->descriptions["Sin"] = "<p>Description not yet filled!</p>";
    d->tags["Sin"] = QStringList() << "number" << "operator" << "unary" << "sin";
    d->types["Sin"] = "sin";

    d->nodes << "Square";
    d->descriptions["Square"] = "<p>Description not yet filled!</p>";
    d->tags["Square"] = QStringList() << "number" << "operator" << "unary" << "square";
    d->types["Square"] = "square";

    d->nodes << "Sqrt";
    d->descriptions["Sqrt"] = "<p>Description not yet filled!</p>";
    d->tags["Sqrt"] = QStringList() << "number" << "operator" << "unary" << "sqrt";
    d->types["Sqrt"] = "sqrt";

    d->nodes << "Tan";
    d->descriptions["Tan"] = "<p>Description not yet filled!</p>";
    d->tags["Tan"] = QStringList() << "number" << "operator" << "unary" << "tan";
    d->types["Tan"] = "tan";

    d->nodes << "Eucldiv";
    d->descriptions["Eucldiv"] = "<p>Description not yet filled!</p>";
    d->tags["Eucldiv"] = QStringList() << "number" << "operator" << "binary" << "eucldiv";
    d->types["Eucldiv"] = "eucldiv";

    d->nodes << "Expn";
    d->descriptions["Expn"] = "<p>Description not yet filled!</p>";
    d->tags["Expn"] = QStringList() << "number" << "operator" << "binary" << "expn";
    d->types["Expn"] = "expn";

    d->nodes << "Logn";
    d->descriptions["Logn"] = "<p>Description not yet filled!</p>";
    d->tags["Logn"] = QStringList() << "number" << "operator" << "binary" << "logn";
    d->types["Logn"] = "logn";

    d->nodes << "Minus";
    d->descriptions["Minus"] = "<p>Description not yet filled!</p>";
    d->tags["Minus"] = QStringList() << "number" << "operator" << "binary" << "minus";
    d->types["Minus"] = "minus";

    d->nodes << "Modulo";
    d->descriptions["Modulo"] = "<p>Description not yet filled!</p>";
    d->tags["Modulo"] = QStringList() << "number" << "operator" << "binary" << "modulo";
    d->types["Modulo"] = "modulo";

    d->nodes << "Mult";
    d->descriptions["Mult"] = "<p>Description not yet filled!</p>";
    d->tags["Mult"] = QStringList() << "number" << "operator" << "binary" << "mult";
    d->types["Mult"] = "mult";

    d->nodes << "Plus";
    d->descriptions["Plus"] = "<p>Description not yet filled!</p>";
    d->tags["Plus"] = QStringList() << "number" << "operator" << "binary" << "plus";
    d->types["Plus"] = "plus";

    d->nodes << "Posnthroot";
    d->descriptions["Posnthroot"] = "<p>Description not yet filled!</p>";
    d->tags["Posnthroot"] = QStringList() << "number" << "operator" << "binary" << "posnthroot";
    d->types["Posnthroot"] = "posnthroot";

    d->nodes << "Power";
    d->descriptions["Power"] = "<p>Description not yet filled!</p>";
    d->tags["Power"] = QStringList() << "number" << "operator" << "binary" << "power";
    d->types["Power"] = "power";

    d->nodes << "Ratio";
    d->descriptions["Ratio"] = "<p>Description not yet filled!</p>";
    d->tags["Ratio"] = QStringList() << "number" << "operator" << "binary" << "ratio";
    d->types["Ratio"] = "ratio";

    d->nodes << "Equal";
    d->descriptions["Equal"] = "<p>Description not yet filled!</p>";
    d->tags["Equal"] = QStringList() << "number" << "operator" << "binary" << "equal";
    d->types["Equal"] = "equal";

    d->nodes << "Notequal";
    d->descriptions["Notequal"] = "<p>Description not yet filled!</p>";
    d->tags["Notequal"] = QStringList() << "number" << "operator" << "binary" << "notequal";
    d->types["Notequal"] = "notequal";

    d->nodes << "Gt";
    d->descriptions["Gt"] = "<p>Description not yet filled!</p>";
    d->tags["Gt"] = QStringList() << "number" << "operator" << "binary" << "gt";
    d->types["Gt"] = "gt";

    d->nodes << "Lt";
    d->descriptions["Lt"] = "<p>Description not yet filled!</p>";
    d->tags["Lt"] = QStringList() << "number" << "operator" << "binary" << "lt";
    d->types["Lt"] = "lt";

    d->nodes << "Gte";
    d->descriptions["Gte"] = "<p>Description not yet filled!</p>";
    d->tags["Gte"] = QStringList() << "number" << "operator" << "binary" << "gte";
    d->types["Gte"] = "gte";

    d->nodes << "Lte";
    d->descriptions["Lte"] = "<p>Description not yet filled!</p>";
    d->tags["Lte"] = QStringList() << "number" << "operator" << "binary" << "lte";
    d->types["Lte"] = "lte";

    d->nodes << "Almosteq";
    d->descriptions["Almosteq"] = "<p>Description not yet filled!</p>";
    d->tags["Almosteq"] = QStringList() << "number" << "operator" << "binary" << "almosteq";
    d->types["Almosteq"] = "almosteq";

    d->nodes << "Notalmosteq";
    d->descriptions["Notalmosteq"] = "<p>Description not yet filled!</p>";
    d->tags["Notalmosteq"] = QStringList() << "number" << "operator" << "binary" << "notalmosteq";
    d->types["Notalmosteq"] = "notalmosteq";

// /////////////////////////////////////////////////////////////////

    d->nodes << "Not";
    d->descriptions["Not"] = "<p>Description not yet filled!</p>";
    d->tags["Not"] = QStringList() << "boolean" << "operator" << "unary" << "not";
    d->types["Not"] = "not";

    d->nodes << "And";
    d->descriptions["And"] = "<p>Description not yet filled!</p>";
    d->tags["And"] = QStringList() << "boolean" << "operator" << "binary" << "and";
    d->types["And"] = "and";

    d->nodes << "Or";
    d->descriptions["Or"] = "<p>Description not yet filled!</p>";
    d->tags["Or"] = QStringList() << "boolean" << "operator" << "binary" << "or";
    d->types["Or"] = "or";

    d->nodes << "Xor";
    d->descriptions["Xor"] = "<p>Description not yet filled!</p>";
    d->tags["Xor"] = QStringList() << "boolean" << "operator" << "binary" << "xor";
    d->types["Xor"] = "xor";

    d->nodes << "Nand";
    d->descriptions["Nand"] = "<p>Description not yet filled!</p>";
    d->tags["Nand"] = QStringList() << "boolean" << "operator" << "binary" << "nand";
    d->types["Nand"] = "nand";

    d->nodes << "Nor";
    d->descriptions["Nor"] = "<p>Description not yet filled!</p>";
    d->tags["Nor"] = QStringList() << "boolean" << "operator" << "binary" << "nor";
    d->types["Nor"] = "nor";

    d->nodes << "Xnor";
    d->descriptions["Xnor"] = "<p>Description not yet filled!</p>";
    d->tags["Xnor"] = QStringList() << "boolean" << "operator" << "binary" << "xnor";
    d->types["Xnor"] = "xnor";

    d->nodes << "Imp";
    d->descriptions["Imp"] = "<p>Description not yet filled!</p>";
    d->tags["Imp"] = QStringList() << "boolean" << "operator" << "binary" << "imp";
    d->types["Imp"] = "imp";

    d->nodes << "Nimp";
    d->descriptions["Nimp"] = "<p>Description not yet filled!</p>";
    d->tags["Nimp"] = QStringList() << "boolean" << "operator" << "binary" << "nimp";
    d->types["Nimp"] = "nimp";

    // control nodes

    d->nodes << "Do While";
    d->descriptions["Do While"] = "<p>Description not yet filled!</p>";
    d->tags["Do While"] = QStringList() << "control" << "do" << "while";
    d->types["Do While"] = "do while";

    d->nodes << "If";
    d->descriptions["If"] = dtkReadFile(":dtkComposer/dtkComposerNodeControlIf.html");
    d->tags["If"] = QStringList() << "control" << "if";
    d->types["If"] = "if";

    d->nodes << "For";
    d->descriptions["For"] = "<p>Description not yet filled!</p>";
    d->tags["For"] = QStringList() << "control" << "for";
    d->types["For"] = "for";

    d->nodes << "Foreach";
    d->descriptions["Foreach"] = "<p>Description not yet filled!</p>";
    d->tags["Foreach"] = QStringList() << "control" << "foreach";
    d->types["Foreach"] = "foreach";

    d->nodes << "While";
    d->descriptions["While"] = "<p>Description not yet filled!</p>";
    d->tags["While"] = QStringList() << "control" << "while";
    d->types["While"] = "while";

    // log nodes
    d->nodes << "Logger";
    d->descriptions["Logger"] = "<p>Description not yet filled!</p>";
    d->tags["Logger"] = QStringList() << "logger" << "debug";
    d->types["Logger"] = "logger";

    // process nodes
    d->nodes << "Process";
    d->descriptions["Process"] = "<p>Description not yet filled!</p>";
    d->tags["Process"] = QStringList() << "process" ;
    d->types["Process"] = "process";

    // dtkDistributed nodes
    d->nodes << "World";
    d->tags["World"] = QStringList() <<  "distributed" ;
    d->types["World"] = "world";

    d->nodes << "MpiWorld";
    d->tags["MpiWorld"] = QStringList() <<  "distributed" << "mpi";
    d->types["MpiWorld"] = "mpiworld";

    d->nodes << "CommunicatorRank";
    d->tags["CommunicatorRank"] = QStringList() <<  "rank" << "distributed" << "mpi" << "communicator";
    d->types["CommunicatorRank"] = "communicatorRank";

    d->nodes << "CommunicatorSize";
    d->tags["CommunicatorSize"] = QStringList() <<  "size" << "distributed" << "mpi" << "communicator";
    d->types["CommunicatorSize"] = "communicatorSize";

    d->nodes << "CommunicatorInit";
    d->tags["CommunicatorInit"] = QStringList() <<  "initialization" << "distributed" << "mpi" << "communicator";
    d->types["CommunicatorInit"] = "communicatorInit";

    d->nodes << "CommunicatorUninitialize";
    d->tags["CommunicatorUninitialize"] = QStringList() <<  "finalize" << "distributed" << "mpi" << "communicator";
    d->types["CommunicatorUninitialize"] = "communicatorUninitialize";

    d->nodes << "CommunicatorSendInteger";
    d->tags["CommunicatorSendInteger"] = QStringList() <<  "send" << "distributed" << "mpi" << "communicator" << "integer";
    d->types["CommunicatorSendInteger"] = "communicatorSendInteger";

    d->nodes << "CommunicatorReceiveInteger";
    d->tags["CommunicatorReceiveInteger"] = QStringList() <<  "receive" << "distributed" << "mpi" << "communicator" << "integer";;
    d->types["CommunicatorReceiveInteger"] = "communicatorReceiveInteger";

    d->nodes << "CommunicatorSendReal";
    d->tags["CommunicatorSendReal"] = QStringList() <<  "send" << "distributed" << "mpi" << "communicator" << "real";
    d->types["CommunicatorSendReal"] = "communicatorSendReal";

    d->nodes << "CommunicatorReceiveReal";
    d->tags["CommunicatorReceiveReal"] = QStringList() <<  "receive" << "distributed" << "mpi" << "communicator" << "real";;
    d->types["CommunicatorReceiveReal"] = "communicatorReceiveReal";

    d->nodes << "CommunicatorReceive";
    d->tags["CommunicatorReceive"] = QStringList() <<  "receive" << "distributed" << "mpi" << "communicator";;
    d->types["CommunicatorReceive"] = "communicatorReceive";

    d->nodes << "CommunicatorSend";
    d->tags["CommunicatorSend"] = QStringList() <<  "send" << "distributed" << "mpi" << "communicator";;
    d->types["CommunicatorSend"] = "communicatorSend";

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

    if(type == "file")
        return new dtkComposerNodeFile;

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

    // logger nodes

    if(type == "logger")
        return new dtkComposerNodeLogger;

    // process nodes

    if(type == "process")
        return new dtkComposerNodeProcess;

    // communicator nodes

    if(type == "world")
        return new dtkComposerNodeWorld;

    if(type == "mpiworld")
        return new dtkComposerNodeMpiWorld;

    if(type == "communicatorSize")
        return new dtkComposerNodeCommunicatorSize;

    if(type == "communicatorRank")
        return new dtkComposerNodeCommunicatorRank;

    if(type == "communicatorUninitialize")
        return new dtkComposerNodeCommunicatorUninitialize;

    if(type == "communicatorInit")
        return new dtkComposerNodeCommunicatorInit;

    if(type == "communicatorSendInteger")
        return new dtkComposerNodeCommunicatorSendInteger;

    if(type == "communicatorReceiveInteger")
        return new dtkComposerNodeCommunicatorReceiveInteger;

    if(type == "communicatorSendReal")
        return new dtkComposerNodeCommunicatorSendReal;

    if(type == "communicatorReceiveReal")
        return new dtkComposerNodeCommunicatorReceiveReal;

    if(type == "communicatorSend")
        return new dtkComposerNodeCommunicatorSend;

    if(type == "communicatorReceive")
        return new dtkComposerNodeCommunicatorReceive;

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
