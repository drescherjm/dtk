/* dtkComposerNodeNumberComparator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar  7 09:22:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:33:05 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#ifndef DTKCOMPOSERNODENUMBERCOMPARATOR_H
#define DTKCOMPOSERNODENUMBERCOMPARATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeNumberComparatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparator : public dtkComposerNode
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
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeNumberComparatorPrivate *d;
};

#endif
