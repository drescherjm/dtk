/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 12 11:25:50 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul 13 10:27:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H

#include "dtkComposerNode.h"

class dtkComposerNodeStringPrivate;

class dtkComposerNodeString : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeString(dtkComposerNode *parent = 0);
    ~dtkComposerNodeString(void);

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
