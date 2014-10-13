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

public:
    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

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

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

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

public:
    inline QString type(void) {
        return "not";
    }

    inline QString titleHint(void) {
        return "Not";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - AND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryAnd : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "and";
    }

    inline QString titleHint(void) {
        return "And";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - OR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryOr : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "or";
    }

    inline QString titleHint(void) {
        return "Or";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryXor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "xor";
    }

    inline QString titleHint(void) {
        return "Xor";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NAND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNand : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "nand";
    }

    inline QString titleHint(void) {
        return "Nand";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "nor";
    }

    inline QString titleHint(void) {
        return "Nor";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XNOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryXnor : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "xnor";
    }

    inline QString titleHint(void) {
        return "Xnor";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - IMP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryImp : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "imp";
    }

    inline QString titleHint(void) {
        return "Imp";
    }
};

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NIMP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperatorBinaryNimp : public dtkComposerNodeBooleanOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "nimp";
    }

    inline QString titleHint(void) {
        return "Nimp";
    }
};
