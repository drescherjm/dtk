/* @(#)dtkComposerNodeProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: jeu. mars 29 13:17:02 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 3
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


#endif /* DTKCOMPOSERNODEPROCESS_H */

