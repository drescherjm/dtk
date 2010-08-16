/* dtkComposerNodeCondition.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 12 13:51:03 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul 13 10:24:15 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONDITION_H
#define DTKCOMPOSERNODECONDITION_H

#include "dtkComposerNode.h"

class dtkComposerNodeConditionPrivate;

class dtkComposerNodeCondition : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeCondition(dtkComposerNode *parent = 0);
    ~dtkComposerNodeCondition(void);

private:
    dtkComposerNodeConditionPrivate *d;
};

#endif
