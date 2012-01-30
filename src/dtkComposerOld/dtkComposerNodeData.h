/* dtkComposerNodeData.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:21:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 24 15:09:27 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEDATA_H
#define DTKCOMPOSERNODEDATA_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeDataPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeData : public dtkComposerNode
{
    Q_OBJECT

public:
             dtkComposerNodeData(dtkComposerNode *parent = 0);
    virtual ~dtkComposerNodeData(void);

protected:
    virtual void run(void);

private:
    dtkComposerNodeDataPrivate *d;
};

#endif
