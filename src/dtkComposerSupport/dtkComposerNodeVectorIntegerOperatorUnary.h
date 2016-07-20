/* dtkComposerNodeVectorIntegerOperatorUnary.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 15:57:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:15:43 2012 (+0200)
 *           By: tkloczko
 *     Update #: 13
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORINTEGEROPERATORUNARY_H
#define DTKCOMPOSERNODEVECTORINTEGEROPERATORUNARY_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorUnaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorUnary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerOperatorUnary(void);
    ~dtkComposerNodeVectorIntegerOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorUnaryScalarPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorUnaryScalar : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerOperatorUnaryScalar(void);
    ~dtkComposerNodeVectorIntegerOperatorUnaryScalar(void);

    inline QString inputLabelHint(int port) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorUnaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnary UNITARY interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorUnaryUnitary : public dtkComposerNodeVectorIntegerOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_unit";
    }

    inline QString titleHint(void) {
        return "VectorInteger Unit";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnaryScalar NORM interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorUnaryScalarNorm : public dtkComposerNodeVectorIntegerOperatorUnaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_norm";
    }

    inline QString titleHint(void) {
        return "VectorInteger Norm";
    }
};

#endif
