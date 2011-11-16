/* dtkComposerNodeStringOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 15:36:32 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 13
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

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);
    bool  onLeftRouteConnected(dtkComposerEdge *route);
    bool onRightRouteConnected(dtkComposerEdge *route);

private:
    dtkComposerNodeStringOperatorPrivate *d;
};

#endif
