/* dtkComposerNodeBooleanOperator.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:51:36 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Unary boolean operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorUnary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeBooleanOperatorUnary(void);
    ~dtkComposerNodeBooleanOperatorUnary(void);

protected:
    dtkComposerNodeBooleanOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeBooleanOperatorBinary(void);
    ~dtkComposerNodeBooleanOperatorBinary(void);

protected:
    dtkComposerNodeBooleanOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Unary boolean operator - NOT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorUnaryNot : public dtkComposerNodeBooleanOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - AND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryAnd : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - OR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryOr : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryXor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NAND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNand : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XNOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryXnor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - IMP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryImp : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NIMP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNimp : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

};
