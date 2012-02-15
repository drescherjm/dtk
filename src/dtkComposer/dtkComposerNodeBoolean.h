/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:46:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 17:45:06 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeBoolean(void);
    ~dtkComposerNodeBoolean(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "boolean";
    }

    inline QString titleHint(void) {
        return "Boolean";
    }

    inline QString labelHint(int port) {
        return "value";
    }

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
