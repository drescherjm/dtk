/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 25 14:58:42 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEANOPERATOR_H
#define DTKCOMPOSERNODEBOOLEANOPERATOR_H

#include "dtkComposerNode.h"

class dtkComposerNodeBooleanOperatorPrivate;

class dtkComposerNodeBooleanOperator : public dtkComposerNode
{
    Q_OBJECT

public:
    enum Operation {
        And,
        Or,
        Xor,
        Nand,
        Nor,
        Xnor,
        Imp,
        Nimp        
    };

public:
     dtkComposerNodeBooleanOperator(dtkComposerNode *parent = 0);
    ~dtkComposerNodeBooleanOperator(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeBooleanOperatorPrivate *d;
};

#endif
