/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:27:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 23:29:13 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
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
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeView : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeView(void);
    ~dtkComposerNodeView(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeViewPrivate *d;
};

#endif
