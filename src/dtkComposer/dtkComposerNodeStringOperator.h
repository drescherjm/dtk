/* @(#)dtkComposerNodeStringOperator.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/20 14:34:00
 * Version: $Id$
 * Last-Updated: lun. avril 23 09:26:09 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODESTRINGOPERATOR_H
#define DTKCOMPOSERNODESTRINGOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorUnary(void);
    ~dtkComposerNodeStringOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeStringOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorBinary(void);
    ~dtkComposerNodeStringOperatorBinary(void);

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
    dtkComposerNodeStringOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary - Append
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinaryAppend : public dtkComposerNodeStringOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "append";
    }

    inline QString titleHint(void) {
        return "Append";
    }
};



#endif /* DTKCOMPOSERNODESTRINGOPERATOR_H */

