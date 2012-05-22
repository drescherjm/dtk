/* dtkComposerNodeVectorRealOperatorUnary.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 15:57:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 16:44:41 2012 (+0200)
 *           By: sblekout
 *     Update #: 12
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef dtkComposerNodeVectorRealOperatorUnary_H
#define dtkComposerNodeVectorRealOperatorUnary_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorUnary : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorUnaryScalar : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorUnaryUnitary : public dtkComposerNodeVectorRealOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorUnaryScalarNorm : public dtkComposerNodeVectorRealOperatorUnaryScalar
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
