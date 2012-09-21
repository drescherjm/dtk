/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 21 18:20:04 2012 (+0200)
 *           By: tkloczko
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_P_H
#define DTKCOMPOSERTRANSMITTERVARIANT_P_H

#include <QtCore>

class dtkComposerTransmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    dtkComposerTransmitterVariantPrivate(void)
        {
            type_conversions.insert(QMetaType::Bool, QMetaType::Bool);
            type_conversions.insert(qMetaTypeId<bool*>(0), QMetaType::Bool);
            type_conversions.insert(QMetaType::Int, QMetaType::Int);
            type_conversions.insert(qMetaTypeId<int*>(0), QMetaType::Int);
            type_conversions.insert(QMetaType::LongLong, QMetaType::LongLong);
            type_conversions.insert(qMetaTypeId<qlonglong*>(0), QMetaType::LongLong);
            type_conversions.insert(QMetaType::UInt, QMetaType::UInt);
            type_conversions.insert(qMetaTypeId<uint*>(0), QMetaType::UInt);
            type_conversions.insert(QMetaType::ULongLong, QMetaType::ULongLong);
            type_conversions.insert(qMetaTypeId<qulonglong*>(0), QMetaType::ULongLong);
            type_conversions.insert(QMetaType::Double, QMetaType::Double);
            type_conversions.insert(qMetaTypeId<qreal*>(0), QMetaType::Double);
            type_conversions.insert(QMetaType::QString, QMetaType::QString);
            type_conversions.insert(qMetaTypeId<QString*>(0), QMetaType::QString);
        }
        
public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QList<int> data_types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;

    bool already_ask;
    
public:
    bool      value_b;
    qlonglong value_i;
    qreal     value_r;
    QString   value_s;
    
public:
    QHash<int, int> type_conversions;

public:
    QVariant m_variant;
};

#endif
