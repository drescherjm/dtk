/* @(#)dtkComposerNodeWorld.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 12:58:15
 * Version: $Id$
 * Last-Updated: mar. avril  3 17:28:17 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 16
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEWORLD_H
#define DTKCOMPOSERNODEWORLD_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeComposite.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorld declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeWorldPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeWorld : public dtkComposerNodeComposite
{
public:
             dtkComposerNodeWorld(void);
    virtual ~dtkComposerNodeWorld(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public:
    void begin(void);
    void end(void);

private:
    dtkComposerNodeWorldPrivate *d;
};

#endif /* DTKCOMPOSERNODEWORLD_H */

