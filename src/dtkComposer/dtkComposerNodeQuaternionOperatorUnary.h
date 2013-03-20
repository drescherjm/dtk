/* dtkComposerNodeQuaternionOperatorUnary.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:19:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 14:53:27 2012 (+0200)
 *           By: tkloczko
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEQUATERNIONOPERATORUNARY_H
#define DTKCOMPOSERNODEQUATERNIONOPERATORUNARY_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryPrivate;

class  dtkComposerNodeQuaternionOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeQuaternionOperatorUnary(void);
    ~dtkComposerNodeQuaternionOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "quat";
    }

    inline QString outputLabelHint(int) {
        return "quat";
    }

protected:
    dtkComposerNodeQuaternionOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryScalarPrivate;

class  dtkComposerNodeQuaternionOperatorUnaryScalar : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeQuaternionOperatorUnaryScalar(void);
    ~dtkComposerNodeQuaternionOperatorUnaryScalar(void);

    inline QString inputLabelHint(int port) {
        return "quat";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeQuaternionOperatorUnaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary UNITARY interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeQuaternionOperatorUnaryUnitary : public dtkComposerNodeQuaternionOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_unit";
    }

    inline QString titleHint(void) {
        return "Quat Unit";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar NORM interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeQuaternionOperatorUnaryScalarNorm : public dtkComposerNodeQuaternionOperatorUnaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_norm";
    }

    inline QString titleHint(void) {
        return "Quat Norm";
    }
};

#endif
