/* dtkComposerNodeVector.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 16:50:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:04:34 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVECTOR_H
#define DTKCOMPOSERNODEVECTOR_H

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVectorPrivate;

class dtkComposerNodeVector : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVector(void);
    ~dtkComposerNodeVector(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector";
    }

    inline QString titleHint(void) {
        return "Vector";
    }

    inline QString inputLabelHint(int) {
        return "values";
    }

    inline QString outputLabelHint(int) {
        return "values";
    }

private:
    dtkComposerNodeVectorPrivate *d;
};

#endif
