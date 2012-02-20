/* dtkComposerNodeComposite.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 20 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 16:11:00 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 5
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODECOMPOSITE_H
#define DTKCOMPOSERNODECOMPOSITE_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeComposite : public dtkComposerNode
{
public:
             dtkComposerNodeComposite(void);
    virtual ~dtkComposerNodeComposite(void);

public:
    QString type(void);

private:
    dtkComposerNodeCompositePrivate *d;
};

#endif
