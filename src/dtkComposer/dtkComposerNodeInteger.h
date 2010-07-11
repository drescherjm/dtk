/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jul 11 19:17:42 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jul 11 19:19:15 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEINTEGER_H
#define DTKCOMPOSERNODEINTEGER_H

#include "dtkComposerNode.h"

class dtkComposerNodeIntegerPrivate;

class dtkComposerNodeInteger : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeInteger(dtkComposerNode *parent = 0);
    ~dtkComposerNodeInteger(void);

private:
    dtkComposerNodeIntegerPrivate *d;
};

#endif
