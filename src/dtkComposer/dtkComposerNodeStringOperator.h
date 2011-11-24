/* dtkComposerNodeStringOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 11:13:56 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRINGOPERATOR_H
#define DTKCOMPOSERNODESTRINGOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeStringOperatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperator : public dtkComposerNode
{
    Q_OBJECT

public:
    enum Operation {
        Append,
        Prepend
    };

public:
     dtkComposerNodeStringOperator(dtkComposerNode *parent = 0);
    ~dtkComposerNodeStringOperator(void);

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
    bool onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);

    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeStringOperatorPrivate *d;
};

#endif
