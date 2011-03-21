/* dtkComposerNodeLog.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 20:49:22 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 13:23:44 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOG_H
#define DTKCOMPOSERNODELOG_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeLogPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLog : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeLog(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLog(void);

protected:
    void onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeLogPrivate *d;
};

#endif
