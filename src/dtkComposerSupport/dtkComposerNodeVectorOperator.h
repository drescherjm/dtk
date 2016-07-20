/* dtkComposerNodeVectorOperator.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 17:09:00 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:17:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTOROPERATOR_H
#define DTKCOMPOSERNODEVECTOROPERATOR_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Unary vector operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorOperatorUnaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorOperatorUnary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorOperatorUnary(void);
    ~dtkComposerNodeVectorOperatorUnary(void);

public:
    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeVectorOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Binary vector operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorOperatorBinaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorOperatorBinary(void);
    ~dtkComposerNodeVectorOperatorBinary(void);

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
    dtkComposerNodeVectorOperatorBinaryPrivate *d;
};

#endif
