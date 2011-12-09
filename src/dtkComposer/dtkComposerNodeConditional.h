/* dtkComposerNodeConditional.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:59:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 17:05:23 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 19
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
    bool evaluate(dtkComposerEvaluatorPrivate *evaluator);

public:
    bool  onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination);
    bool onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);

public:
    void      appendSourceRoutes(dtkComposerRoute *route);
    void appendDestinationRoutes(dtkComposerRoute *route);

    void      appendSourceNodes(dtkComposerEdge *route);
    void appendDestinationNodes(dtkComposerEdge *route);

private:
    dtkComposerNodeConditionalPrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif
