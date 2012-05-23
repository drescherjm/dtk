/* @(#)dtkComposerNodeProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: Tue Apr 24 21:18:03 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
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
