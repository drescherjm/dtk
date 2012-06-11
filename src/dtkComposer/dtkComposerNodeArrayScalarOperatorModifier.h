/* dtkComposerNodeArrayScalarOperatorModifier.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Thu Apr 26 16:14:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:17:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 39
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEARRAYSCALAROPERATORMODIFIER_H
#define DTKCOMPOSERNODEARRAYSCALAROPERATORMODIFIER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorModifier : public dtkComposerNodeLeaf
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
// dtkComposerNodeArrayScalarOperator - INSERT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorInsert : public dtkComposerNodeArrayScalarOperatorModifier
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
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorSum : public dtkComposerNodeArrayScalarOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorSubstract : public dtkComposerNodeArrayScalarOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorMult : public dtkComposerNodeArrayScalarOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorDivide : public dtkComposerNodeArrayScalarOperatorModifier
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
