/* dtkComposerNodeData.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:21:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul 15 11:21:43 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEDATA_H
#define DTKCOMPOSERNODEDATA_H

#include "dtkComposerNode.h"

class dtkComposerNodeDataPrivate;

class dtkComposerNodeData : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeData(dtkComposerNode *parent = 0);
    ~dtkComposerNodeData(void);

private:
    dtkComposerNodeDataPrivate *d;
};

#endif
