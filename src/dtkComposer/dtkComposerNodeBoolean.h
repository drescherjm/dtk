/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:46:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 08:47:05 2012 (+0100)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeBoolean(void);
    ~dtkComposerNodeBoolean(void);

public:
    void run(void);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
