/* dtkComposerNodeProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov  1 16:37:27 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
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

    virtual QString implementation(void);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
