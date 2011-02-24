/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:24:46 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 16:48:13 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 7
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
    virtual void onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    virtual void run(void);

private:
    dtkComposerNodeViewPrivate *d;
};

#endif
