/* dtkComposerNodeProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 26 13:53:13 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPROCESS_H
#define DTKCOMPOSERNODEPROCESS_H

#include "dtkComposerNode.h"

class dtkComposerNodeProcessPrivate;

class dtkComposerNodeProcess : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeProcess(dtkComposerNode *parent = 0);
    ~dtkComposerNodeProcess(void);

    QVariant value(dtkComposerNodeProperty *property);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
