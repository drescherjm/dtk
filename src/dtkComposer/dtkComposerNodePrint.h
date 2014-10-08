/* dtkComposerNodePrint.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Mon Mar 26 12:40:45 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPRINT_H
#define DTKCOMPOSERNODEPRINT_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodePrintPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePrint : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodePrint(void);
    ~dtkComposerNodePrint(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "print";
    }

    inline QString titleHint(void) {
        return "Print";
    }

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "stdout";
        else if (port == 1)
            return "stderr";
        else
            return "value";
    }

private:
    dtkComposerNodePrintPrivate *d;
};

#endif
