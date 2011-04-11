/* dtkComposerNodeLoop.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:21:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:30:33 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOP_H
#define DTKCOMPOSERNODELOOP_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeLoopPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoop : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeLoop(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoop(void);

public slots:
    void update(void);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeLoopPrivate *d;
};

#endif
