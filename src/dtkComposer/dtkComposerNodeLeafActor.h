/* dtkComposerNodeLeafActor.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: jeu. oct. 10 09:56:25 2013 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELEAFACTOR_H
#define DTKCOMPOSERNODELEAFACTOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkAbstractActor;
class dtkComposerNodeLeafActorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafActor interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeLeafActor : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafActor(void);
    virtual ~dtkComposerNodeLeafActor(void);

private:
    dtkComposerNodeLeafActorPrivate *d;
};

#endif
