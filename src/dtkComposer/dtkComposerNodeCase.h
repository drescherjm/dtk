/* dtkComposerNodeCase.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:01:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 21:58:18 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECASE_H
#define DTKCOMPOSERNODECASE_H

#include "dtkComposerNodeControl.h"

class dtkComposerNodeCasePrivate;

class dtkComposerNodeCase : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeCase(dtkComposerNode *parent = 0);
    ~dtkComposerNodeCase(void);

    dtkComposerNodeControlBlock *addBlock(const QString& title);

public:
    void layout(void);

public slots:
    void update(void);

private:
    dtkComposerNodeCasePrivate *d;
};

#endif
