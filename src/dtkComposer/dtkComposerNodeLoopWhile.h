/* dtkComposerNodeLoopWhile.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May  4 08:44:22 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 15:22:24 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOPWHILE_H
#define DTKCOMPOSERNODELOOPWHILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLoop.h"

class dtkComposerNodeLoopWhilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoopWhile : public dtkComposerNodeLoop
{
    Q_OBJECT

public:
     dtkComposerNodeLoopWhile(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoopWhile(void);

public:
    void layout(void);

public slots:
    void update(void);

private:
    dtkComposerNodeLoopWhilePrivate *d;
};

#endif

