/* dtkComposerNodeNumber.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:19:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 16:39:29 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 102
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

class dtkComposerNodeAbstractTransmitter;
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

public:
    QVariant value(void);
    void setValue(QVariant value);

public:
    void expand(void);
    void collapse(void);

public slots:
    void touch(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool setReceiver(dtkComposerEdge *route, dtkComposerNodeProperty *destination);

    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    bool interactive(void) const;

    void  setLabelText(const QString& value);
    void setEditorText(const QString& value);

private:
    void setTransmitterData(const QString& value);

public:
    static Genre compatibleType(const QString& left_type, const QString& right_type);
    static Genre genre(QVariant& a, QVariant& b);

private:
    dtkComposerNodeNumberPrivate *d;
};

#endif
