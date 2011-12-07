/* dtkComposerNodeCase.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:01:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 11:58:04 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECASE_H
#define DTKCOMPOSERNODECASE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"
 
class dtkComposerEdge;
class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;

class dtkComposerNodeCasePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCase : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeCase(dtkComposerNode *parent = 0);
    ~dtkComposerNodeCase(void);

public:
    dtkComposerNodeControlBlock *createBlock(const QString& title);

public:
    void layout(void);

public slots:
    bool evaluate(dtkComposerEvaluatorPrivate *evaluator);

protected:
    void pull(dtkComposerRoute *i_route, dtkComposerNodeProperty *property);
    void push(dtkComposerRoute *o_route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeCasePrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif
