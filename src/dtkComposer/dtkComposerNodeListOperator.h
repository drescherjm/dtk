/* dtkComposerNodeListOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 17:09:00 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:14:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELISTOPERATOR_H
#define DTKCOMPOSERNODELISTOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Unary list operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeListOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeListOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeListOperatorUnary(void);
    ~dtkComposerNodeListOperatorUnary(void);

public:
    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeListOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Binary list operator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeListOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeListOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeListOperatorBinary(void);
    ~dtkComposerNodeListOperatorBinary(void);

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
    dtkComposerNodeListOperatorBinaryPrivate *d;
};

#endif
