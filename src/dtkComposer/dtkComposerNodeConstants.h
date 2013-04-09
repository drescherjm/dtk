/* dtkComposerNodeConstants.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:13 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate;

class  dtkComposerNodePi : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodePi(void);
    ~dtkComposerNodePi(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "pi";
    }

    inline QString titleHint(void) {
        return "Pi";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodePiPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate;

class  dtkComposerNodeE : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeE(void);
    ~dtkComposerNodeE(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "e";
    }

    inline QString titleHint(void) {
        return "E";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeEPrivate *d;
};
