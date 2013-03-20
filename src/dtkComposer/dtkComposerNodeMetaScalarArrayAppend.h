/* dtkComposerNodeMetaScalarArray.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Jul 13 16:04:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul 13 21:57:56 2012 (+0200)
 *           By: Régis Duvigneau
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETASCALARARRAYAPPEND_H
#define DTKCOMPOSERNODEMETASCALARARRAYAPPEND_H



#include <dtkComposer/dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaScalarArrayAppendPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayAppend interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeMetaScalarArrayAppend : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMetaScalarArrayAppend(void);
    ~dtkComposerNodeMetaScalarArrayAppend(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_scalar_array_append";
    }

    inline QString titleHint(void) {
        return "Meta Scalar Array Append";
    }

public:
    inline QString inputLabelHint(int port) {

        if(port == 0)
            return "arrays";

        if(port == 1)
            return "array";

        return "input";
    }

    inline QString outputLabelHint(int port) {

        if(port == 0)
            return "arrays";

        return "output";
    }

private:
    dtkComposerNodeMetaScalarArrayAppendPrivate *d;
};

#endif

