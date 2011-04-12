/* dtkComposerNodeNumber.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:19:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:32:00 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 69
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBER_H
#define DTKCOMPOSERNODENUMBER_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeNumberPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumber : public dtkComposerNode
{
    Q_OBJECT

public:
    enum Genre {
          Invalid = QVariant::Invalid,
              Int = QVariant::Int,
             UInt = QVariant::UInt,
             Long = QMetaType::Long,
            ULong = QMetaType::ULong,
         LongLong = QVariant::LongLong,
        ULongLong = QVariant::ULongLong,
            Float = QMetaType::Float,
           Double = QVariant::Double
    };

public:
     dtkComposerNodeNumber(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumber(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    Genre genre(void);
    QVariant number(void);

    void setGenre(Genre genre);
    void setGenre(int genre);
    void setNumber(QVariant number);

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
    void refresh(void);

public:
    void expand(void);
    void collapse(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

public:
    static Genre genre(QVariant& a, QVariant& b);

private:
    dtkComposerNodeNumberPrivate *d;
};

#endif
