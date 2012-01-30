/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:24:46 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:37:05 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVIEW_H
#define DTKCOMPOSERNODEVIEW_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeView : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeView(dtkComposerNode *parent = 0);
    ~dtkComposerNodeView(void);

protected:
    virtual void pull(dtkComposerRoute *edge, dtkComposerNodeProperty *property);
    virtual void  run(void);

private:
    dtkComposerNodeViewPrivate *d;
};

#endif
