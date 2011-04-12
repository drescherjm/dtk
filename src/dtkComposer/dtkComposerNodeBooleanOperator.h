/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:27:22 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 39
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

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeBooleanOperatorPrivate *d;
};

#endif
