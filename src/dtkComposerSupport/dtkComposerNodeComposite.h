/* dtkComposerNodeComposite.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 20 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. avril  3 14:56:48 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODECOMPOSITE_H
#define DTKCOMPOSERNODECOMPOSITE_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeComposite : public dtkComposerNode
{
public:
             dtkComposerNodeComposite(void);
    virtual ~dtkComposerNodeComposite(void);

public:
    QString type(void);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeCompositePrivate *d;
};

#endif
