/* dtkComposerNodeNumber.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:19:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 11:09:58 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBER_H
#define DTKCOMPOSERNODENUMBER_H

#include "dtkComposerNode.h"

class dtkComposerNodeNumberPrivate;

class dtkComposerNodeNumber : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeNumber(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumber(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    QVariant value(void);

    void setValue(int value);
    void setValue(uint value);
    void setValue(long value);
    void setValue(ulong value);
    void setValue(qlonglong value);
    void setValue(qulonglong value);
    void setValue(float value);
    void setValue(double value);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeNumberPrivate *d;
};

#endif
