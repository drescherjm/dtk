/* dtkComposerNodeArrayScalarOperatorModifier.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Thu Apr 26 16:14:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul  5 12:18:51 2012 (+0200)
 *           By: tkloczko
 *     Update #: 41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEARRAYSCALAROPERATORMODIFIER_H
#define DTKCOMPOSERNODEARRAYSCALAROPERATORMODIFIER_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierPrivate;

class  dtkComposerNodeArrayScalarOperatorModifier : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeArrayScalarOperatorModifier(void);
    ~dtkComposerNodeArrayScalarOperatorModifier(void);

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "array";
        else if (port == 1)
            return "index";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "array";
    }

protected:
    dtkComposerNodeArrayScalarOperatorModifierPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierAllPrivate;

class  dtkComposerNodeArrayScalarOperatorModifierAll  : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeArrayScalarOperatorModifierAll(void);
    ~dtkComposerNodeArrayScalarOperatorModifierAll (void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "array";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "array";
    }

protected:
    dtkComposerNodeArrayScalarOperatorModifierAllPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - INSERT
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorInsert : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_insert";
    }

    inline QString titleHint(void) {
        return "Scalar array insert";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Set
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorSet : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_set";
    }

    inline QString titleHint(void) {
        return "Scalar array set";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - APPEND
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorAppend : public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_append";
    }

    inline QString titleHint(void) {
        return "Scalar array append";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierALL - PREPEND
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorPrepend : public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_prepend";
    }

    inline QString titleHint(void) {
        return "Scalar array prepend";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierALL - Add
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorModifierAllAdd : public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_all_add";
    }

    inline QString titleHint(void) {
        return "Scalar array all add";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierALL - Substract
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorModifierAllSubstract : public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_all_substract";
    }

    inline QString titleHint(void) {
        return "Scalar array all substract";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierALL - Mult
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorModifierAllMult : public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_all_mult";
    }

    inline QString titleHint(void) {
        return "Scalar array all mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierALL - Divide
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorModifierAllDivide: public dtkComposerNodeArrayScalarOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_all_divide";
    }

    inline QString titleHint(void) {
        return "Scalar array all divide";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorSum : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_sum";
    }

    inline QString titleHint(void) {
        return "Scalar array sum";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorSubstract : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_substract";
    }

    inline QString titleHint(void) {
        return "Scalar array substract";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorMult : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_mult";
    }

    inline QString titleHint(void) {
        return "Scalar array mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarOperatorDivide : public dtkComposerNodeArrayScalarOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_divide";
    }

    inline QString titleHint(void) {
        return "Scalar array divide";
    }
};

#endif
