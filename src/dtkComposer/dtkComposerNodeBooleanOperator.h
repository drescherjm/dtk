/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 11:11:40 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEANOPERATOR_H
#define DTKCOMPOSERNODEBOOLEANOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeBooleanOperatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperator : public dtkComposerNode
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

public:
    void setOperation(Operation operation);

    Operation operation(void);

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
    dtkComposerNodeBooleanOperatorPrivate *d;
};

#endif
