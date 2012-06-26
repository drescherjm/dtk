/* @(#)dtkComposerNodeProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:22:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPROCESS_H
#define DTKCOMPOSERNODEPROCESS_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeProcess : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeProcess(void);
    ~dtkComposerNodeProcess(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
