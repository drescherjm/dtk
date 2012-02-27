/* dtkComposerNodeList.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 16:50:05 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:01:08 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELIST_H
#define DTKCOMPOSERNODELIST_H

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeListPrivate;

class dtkComposerNodeList : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeList(void);
    ~dtkComposerNodeList(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "list";
    }

    inline QString titleHint(void) {
        return "List";
    }

    inline QString inputLabelHint(int) {
        return "values";
    }

    inline QString outputLabelHint(int) {
        return "values";
    }

private:
    dtkComposerNodeListPrivate *d;
};

#endif
