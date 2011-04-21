/* dtkComposerNodeProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:33:42 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPROCESS_H
#define DTKCOMPOSERNODEPROCESS_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeProcessPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeProcess : public dtkComposerNode
{
    Q_OBJECT

public:
             dtkComposerNodeProcess(dtkComposerNode *parent = 0);
    virtual ~dtkComposerNodeProcess(void);

    QVariant value(dtkComposerNodeProperty *property);

    virtual QString implementation(void);

protected:
    virtual void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void  run(void);
    virtual void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
