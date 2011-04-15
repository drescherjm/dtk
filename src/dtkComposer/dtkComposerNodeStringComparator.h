/* dtkComposerNodeStringComparator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 17:59:17 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:36:38 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRINGCOMPARATOR_H
#define DTKCOMPOSERNODESTRINGCOMPARATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeStringComparatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringComparator : public dtkComposerNode
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
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);    
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeStringComparatorPrivate *d;
};

#endif
