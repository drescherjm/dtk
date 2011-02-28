/* dtkComposerNodeStringComparator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 27 18:27:15 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRINGCOMPARATOR_H
#define DTKCOMPOSERNODESTRINGCOMPARATOR_H

#include "dtkComposerNode.h"

class dtkComposerNodeStringComparatorPrivate;

class dtkComposerNodeStringComparator : public dtkComposerNode
{
    Q_OBJECT

public:
    enum Operation {
        LesserThan,
        LesserThanOrEqual,
        GreaterThan,
        GreaterThanOrEqual,
        Equal,
        Differ
    };

public:
     dtkComposerNodeStringComparator(dtkComposerNode *parent = 0);
    ~dtkComposerNodeStringComparator(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeStringComparatorPrivate *d;
};

#endif
