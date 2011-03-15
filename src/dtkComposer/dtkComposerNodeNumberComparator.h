/* dtkComposerNodeNumberComparator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar  7 09:22:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  7 09:23:24 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#ifndef DTKCOMPOSERNODENUMBERCOMPARATOR_H
#define DTKCOMPOSERNODENUMBERCOMPARATOR_H

#include "dtkComposerNode.h"

class dtkComposerNodeNumberComparatorPrivate;

class dtkComposerNodeNumberComparator : public dtkComposerNode
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
     dtkComposerNodeNumberComparator(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberComparator(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeNumberComparatorPrivate *d;
};

#endif
