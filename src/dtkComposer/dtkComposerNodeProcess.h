/* @(#)dtkComposerNodeProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: Thu Jun 28 14:16:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 9
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
#include "dtkComposerNodeLeafProcess.h"

class dtkComposerNodeProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeProcess : public dtkComposerNodeLeafProcess
{
public:
     dtkComposerNodeProcess(void);
    ~dtkComposerNodeProcess(void);

public:
    bool isAbstractProcess(void) const { return true; }

    QString abstractProcessType(void) const { return "dtkAbstractProcess"; };

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
