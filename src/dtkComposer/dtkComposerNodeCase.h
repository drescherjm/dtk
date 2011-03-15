/* dtkComposerNodeCase.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:01:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 10 14:48:35 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 9
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

    int removeBlock(dtkComposerNodeControlBlock *block, bool clean = false);
    int removeBlock(const QString& title);

public:
    void layout(void);

public slots:
    void update(void);

public:
    QVariant value(dtkComposerNodeProperty *property);

private:
    dtkComposerNodeCasePrivate *d;
};

#endif
