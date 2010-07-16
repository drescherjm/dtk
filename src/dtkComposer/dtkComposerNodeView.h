/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:24:46 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul 15 15:01:02 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVIEW_H
#define DTKCOMPOSERNODEVIEW_H

#include "dtkComposerNode.h"

class dtkComposerNodeViewPrivate;

class dtkComposerNodeView : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeView(dtkComposerNode *parent = 0);
    ~dtkComposerNodeView(void);

protected:
    void onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeViewPrivate *d;
};

#endif
