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

private:
    dtkComposerNodePrintPrivate *d;
};

#endif
