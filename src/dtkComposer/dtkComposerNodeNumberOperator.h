/* dtkComposerNodeNumberOperator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Mar  1 10:13:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 15:16:39 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
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
    void pull(dtkComposerRoute *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerRoute *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool  onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);
    bool onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeNumberOperatorPrivate *d;
};

#endif
