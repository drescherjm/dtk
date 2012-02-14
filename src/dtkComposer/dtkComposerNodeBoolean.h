/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:46:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 16:47:47 2012 (+0100)
 *           By: tkloczko
 *     Update #: 1
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
#include "dtkComposerNode.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNode
{
public:
     dtkComposerNodeBoolean(void);
    ~dtkComposerNodeBoolean(void);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
