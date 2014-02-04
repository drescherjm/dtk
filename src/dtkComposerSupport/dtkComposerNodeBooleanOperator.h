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

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Unary boolean operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorUnary : public dtkComposerNodeLeaf
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinary : public dtkComposerNodeLeaf
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorUnaryNot : public dtkComposerNodeBooleanOperatorUnary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryAnd : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryOr : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryXor : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryNand : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryNor : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryXnor : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryImp : public dtkComposerNodeBooleanOperatorBinary
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBooleanOperatorBinaryNimp : public dtkComposerNodeBooleanOperatorBinary
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
