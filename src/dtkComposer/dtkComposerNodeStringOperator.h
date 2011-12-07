/* dtkComposerNodeStringOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:16:13 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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
    Operation operation(void);

public slots:
    void setOperation(Operation operation);

protected:
    void pull(dtkComposerRoute *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerRoute *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination);
    bool onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeStringOperatorPrivate *d;
};

#endif
