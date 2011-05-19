/* dtkComposerNodeConditional.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:59:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 27 21:54:33 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONDITIONAL_H
#define DTKCOMPOSERNODECONDITIONAL_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerEdge;
class dtkComposerNodeProperty;

class dtkComposerNodeConditionalPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeConditional : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeConditional(dtkComposerNode *parent = 0);
    ~dtkComposerNodeConditional(void);

public:
    void layout(void);

public slots:
    void update(void);

private:
    dtkComposerNodeConditionalPrivate *d;
};

#endif
