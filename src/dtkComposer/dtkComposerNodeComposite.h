/* dtkComposerNodeComposite.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 20 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 08:43:06 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite declaration
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeComposite : public dtkComposerNode
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
