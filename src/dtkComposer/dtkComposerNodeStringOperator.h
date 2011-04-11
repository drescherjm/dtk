/* dtkComposerNodeStringOperator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:34:43 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 12
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

private:
    dtkComposerNodeStringOperatorPrivate *d;
};

#endif
