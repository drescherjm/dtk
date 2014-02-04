/* dtkComposerNodeVector3DOperatorUnary.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 15:57:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 16:44:41 2012 (+0200)
 *           By: tkloczko
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVECTOR3DOPERATORUNARY_H
#define DTKCOMPOSERNODEVECTOR3DOPERATORUNARY_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVector3DOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVector3DOperatorUnary(void);
    ~dtkComposerNodeVector3DOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVector3DOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryScalarPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVector3DOperatorUnaryScalar : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVector3DOperatorUnaryScalar(void);
    ~dtkComposerNodeVector3DOperatorUnaryScalar(void);

    inline QString inputLabelHint(int port) {
        return "vector";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeVector3DOperatorUnaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary UNITARY interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVector3DOperatorUnaryUnitary : public dtkComposerNodeVector3DOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector3D_unit";
    }

    inline QString titleHint(void) {
        return "Vector3D Unit";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar NORM interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVector3DOperatorUnaryScalarNorm : public dtkComposerNodeVector3DOperatorUnaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector3D_norm";
    }

    inline QString titleHint(void) {
        return "Vector3D Norm";
    }
};

#endif
