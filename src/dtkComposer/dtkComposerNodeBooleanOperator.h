/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:51:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:15:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 88
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEANOPERATOR_H
#define DTKCOMPOSERNODEBOOLEANOPERATOR_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Unary boolean operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate;

class  dtkComposerNodeBooleanOperatorUnary : public dtkComposerNodeLeaf
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

class  dtkComposerNodeBooleanOperatorBinary : public dtkComposerNodeLeaf
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

class  dtkComposerNodeBooleanOperatorUnaryNot : public dtkComposerNodeBooleanOperatorUnary
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

class  dtkComposerNodeBooleanOperatorBinaryAnd : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryOr : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryXor : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryNand : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryNor : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryXnor : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryImp : public dtkComposerNodeBooleanOperatorBinary
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

class  dtkComposerNodeBooleanOperatorBinaryNimp : public dtkComposerNodeBooleanOperatorBinary
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

#endif
