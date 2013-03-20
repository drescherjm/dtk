/* dtkComposerNodeVectorInteger.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Thu Apr 26 10:10:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:54:19 2012 (+0200)
 *           By: babette lekouta
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORINTEGER_H
#define DTKCOMPOSERNODEVECTORINTEGER_H


#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVectorIntegerPrivate;

class  dtkComposerNodeVectorInteger : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorInteger(void);
    ~dtkComposerNodeVectorInteger(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger";
    }

    inline QString titleHint(void) {
        return "Vector Integer";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVectorIntegerPrivate *d;
};

#endif
