/* dtkComposerNodeNumberComparator.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar  7 09:22:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 17:42:03 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
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

public:
    Operation operation(void);

    void setOperation(Operation operation);

protected:
    void pull(dtkComposerRoute *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerRoute *edge, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool  onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);
    bool onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeNumberComparatorPrivate *d;
};

#endif
