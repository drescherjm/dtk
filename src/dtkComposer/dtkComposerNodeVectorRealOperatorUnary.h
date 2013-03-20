/* dtkComposerNodeVectorRealOperatorUnary.h ---
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

#ifndef DTKCOMPOSERNODEVECTORREALOPERATORUNARY_H
#define DTKCOMPOSERNODEVECTORREALOPERATORUNARY_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryPrivate;

class  dtkComposerNodeVectorRealOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorUnary(void);
    ~dtkComposerNodeVectorRealOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorRealOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryScalarPrivate;

class  dtkComposerNodeVectorRealOperatorUnaryScalar : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorUnaryScalar(void);
    ~dtkComposerNodeVectorRealOperatorUnaryScalar(void);

    inline QString inputLabelHint(int port) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeVectorRealOperatorUnaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary UNITARY interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeVectorRealOperatorUnaryUnitary : public dtkComposerNodeVectorRealOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_unit";
    }

    inline QString titleHint(void) {
        return "VectorReal Unit";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar NORM interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeVectorRealOperatorUnaryScalarNorm : public dtkComposerNodeVectorRealOperatorUnaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_norm";
    }

    inline QString titleHint(void) {
        return "VectorReal Norm";
    }
};

#endif
