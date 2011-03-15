/* dtkComposerNodeNumberOperator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Mar  1 10:13:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 16:26:16 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBEROPERATOR_H
#define DTKCOMPOSERNODENUMBEROPERATOR_H

#include "dtkComposerNode.h"

class dtkComposerNodeNumberOperatorPrivate;

class dtkComposerNodeNumberOperator : public dtkComposerNode
{
    Q_OBJECT

public:
    enum Operation {
        Addition,
        Substraction,
        Multiplication,
        Division,
        Increment,
        Decrement,
        Modulo,
        Min,
        Max
    };

public:
     dtkComposerNodeNumberOperator(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberOperator(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeNumberOperatorPrivate *d;
};

#endif
