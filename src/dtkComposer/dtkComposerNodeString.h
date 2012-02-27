/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:50:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:50:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeStringPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeString : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeString(void);
    ~dtkComposerNodeString(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "string";
    }

    inline QString titleHint(void) {
        return "String";
    }

    inline QString labelHint(int port) {
        return "value";
    }

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
