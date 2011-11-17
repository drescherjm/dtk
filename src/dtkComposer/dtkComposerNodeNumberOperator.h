/* dtkComposerNodeNumberOperator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Mar  1 10:13:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 14:57:24 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBEROPERATOR_H
#define DTKCOMPOSERNODENUMBEROPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeNumberOperatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperator : public dtkComposerNode
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

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool setReceiver(dtkComposerEdge *route, dtkComposerNodeProperty *destination);

    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeNumberOperatorPrivate *d;
};

#endif
