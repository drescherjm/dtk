/* dtkComposerNodeComposite.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 20 15:40:03 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite declaration
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeComposite : public dtkComposerNode
{
public:
             dtkComposerNodeComposite(void);
    virtual ~dtkComposerNodeComposite(void);

public:
    QString type(void);

public:
    virtual void begin(void);
    virtual void end(void);
};
