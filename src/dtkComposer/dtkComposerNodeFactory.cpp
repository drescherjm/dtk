/* dtkComposerNodeFactory.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Wed Apr 10 12:02:54 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 10 15:11:47 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 169
 */

/* Change Log:
 * 
 */

#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringOperator.h"

dtkComposerNodeFactory::dtkComposerNodeFactory(void) : dtkCorePluginFactory<dtkComposerNode>()
{
    this->initNodeBoolean();
    this->initNodeControl();
    this->initNodeNumber();
    this->initNodeString();

    this->record("composite", &dtkComposerNodeCreator<dtkComposerNodeComposite>);

}

dtkComposerNodeFactory::~dtkComposerNodeFactory(void)
{

}

void dtkComposerNodeFactory::initNodeBoolean(void)
{
    this->record("boolean", &dtkComposerNodeCreator<dtkComposerNodeBoolean>);

    this->record("not", &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorUnaryNot>);

    this->record("and",  &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryAnd>);
    this->record("or",   &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryOr>);
    this->record("xor",  &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXor>);
    this->record("nand", &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNand>);
    this->record("nor",  &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNor>);
    this->record("xnor", &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXnor>);
    this->record("imp",  &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryImp>);
    this->record("nimp", &dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNimp>);
}

void dtkComposerNodeFactory::initNodeControl(void)
{
    this->record("case", &dtkComposerNodeCreator<dtkComposerNodeControlCase>);
    this->record("if",   &dtkComposerNodeCreator<dtkComposerNodeControlIf>);

    this->record("dowhile", &dtkComposerNodeCreator<dtkComposerNodeControlDoWhile>);
    this->record("for",     &dtkComposerNodeCreator<dtkComposerNodeControlFor>);
    this->record("foreach", &dtkComposerNodeCreator<dtkComposerNodeControlForEach>);
    this->record("map",     &dtkComposerNodeCreator<dtkComposerNodeControlMap>);
    this->record("while",   &dtkComposerNodeCreator<dtkComposerNodeControlWhile>);
}

void dtkComposerNodeFactory::initNodeNumber(void)
{
    this->record("integer", &dtkComposerNodeCreator<dtkComposerNodeInteger>);
    this->record("real", &dtkComposerNodeCreator<dtkComposerNodeReal>);

    // -- Unary operators

    this->record("abs",    &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAbs>);
    this->record("sqrt",   &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySqrt>);
    this->record("square", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySquare>);

    this->record("incr", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryIncr>);
    this->record("decr", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDecr>);

    this->record("floor", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryFloor>);
    this->record("ceil",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCeil>);
    this->record("round", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRound>);

    this->record("cos",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCos>);
    this->record("sin",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySin>);
    this->record("tan",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryTan>);
    this->record("acos", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAcos>);
    this->record("asin", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAsin>);
    this->record("atan", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAtan>);

    this->record("deg2rad", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDeg2Rad>);
    this->record("rad2deg", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRad2Deg>);

    this->record("ln",    &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLn>);
    this->record("log10", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLog10>);
    this->record("exp",   &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryExp>);

    // -- Binary operators

    this->record("eucldiv", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryEucldiv>);
    this->record("modulo",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryModulo>);

    this->record("min", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMin>);
    this->record("max", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMax>);

    this->record("plus",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPlus>);
    this->record("minus", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMinus>);
    this->record("mult",  &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMult>);
    this->record("ratio", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryRatio>);

    this->record("logn", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryLogn>);
    this->record("expn", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryExpn>);

    this->record("power",      &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPower>);
    this->record("posnthroot", &dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPosnthroot>);

    // -- Comparator operator

    this->record("equal",    &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorEqual>);
    this->record("notequal", &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorNotequal>);

    this->record("gt",  &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGt>);
    this->record("lt",  &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLt>);
    this->record("gte", &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGte>);
    this->record("lte", &dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLte>);

    this->record("almosteq",    &dtkComposerNodeCreator<dtkComposerNodeNumberAlmosteq>);
    this->record("notalmosteq", &dtkComposerNodeCreator<dtkComposerNodeNumberNotalmosteq>);    
}

void dtkComposerNodeFactory::initNodeString(void)
{
    this->record("string", &dtkComposerNodeCreator<dtkComposerNodeString>);

    this->record("string_append",   &dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryAppend>);
    this->record("string_equality", &dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryLogicEquality>);
}
