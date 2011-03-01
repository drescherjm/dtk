/* dtkComposerNodeNumber.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:19:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 14:37:16 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 33
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
    enum Genre {
        Int,
        UInt,
        Long,
        ULong,
        LongLong,
        ULongLong,
        Float,
        Double
    };

public:
     dtkComposerNodeNumber(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumber(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Genre genre(void);
    QVariant number(void);

    void setGenre(Genre genre);
    bool setNumber(QVariant number);

public:
    void setValue(int value);
    void setValue(uint value);
    void setValue(long value);
    void setValue(ulong value);
    void setValue(qlonglong value);
    void setValue(qulonglong value);
    void setValue(float value);
    void setValue(double value);

public:
    void expand(void);
    void collapse(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeNumberPrivate *d;
};

#endif
