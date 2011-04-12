/* dtkComposerNodeLog.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 20:49:22 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:30:00 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 5
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
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);

private:
    dtkComposerNodeLogPrivate *d;
};

#endif
