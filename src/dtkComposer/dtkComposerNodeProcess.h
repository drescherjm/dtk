/* dtkComposerNodeProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 16:52:41 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 13
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
    virtual void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    virtual void run(void);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
