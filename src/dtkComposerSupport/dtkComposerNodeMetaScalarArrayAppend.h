/* dtkComposerNodeMetaScalarArrayAppend.h ---
 *
 * Author: tkloczko
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEMETASCALARARRAYAPPEND_H
#define DTKCOMPOSERNODEMETASCALARARRAYAPPEND_H

#include "dtkComposerSupportExport.h"

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeMetaScalarArrayAppendPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayAppend interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaScalarArrayAppend : public dtkComposerNodeLeaf
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

        if (port == 0)
            return "arrays";

        if (port == 1)
            return "array";

        return "input";
    }

    inline QString outputLabelHint(int port) {

        if (port == 0)
            return "arrays";

        return "output";
    }

private:
    dtkComposerNodeMetaScalarArrayAppendPrivate *d;
};

#endif

