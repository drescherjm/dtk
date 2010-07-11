/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:26:20 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  9 10:03:59 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerNode.h"

class dtkComposerNodeFilePrivate;

class dtkComposerNodeFile : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeFile(dtkComposerNode *parent = 0);
    ~dtkComposerNodeFile(void);

private:
    dtkComposerNodeFilePrivate *d;
};

#endif
