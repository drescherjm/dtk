/* dtkComposerTransmitterVariant.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:31:25 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  7 16:56:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_TPP
#define DTKCOMPOSERTRANSMITTERVARIANT_TPP

#include "dtkComposerMetatype.h"
#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant_p.h"

#include <dtkContainer/dtkContainerVectorWrapper.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////


template <typename T> inline void dtkComposerTransmitterVariant::setData(T *data)
{
    T t;
    d->type.setValue(t);
    d->variant.setValue(data);
    d->container->reset();
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(dtkContainerVector<T> *data)
{
    dtkAbstractContainerWrapper w;
    d->type.setValue(w);
    d->container = new dtkContainerVectorWrapper<T>(data);
    d->variant.setValue(d->container);
}

template <typename T> inline T *dtkComposerTransmitterVariant::dataFromEmitter(void)
{
    if (e->twinned)
        return d->variant.value<T*>();

    if (e->active_variant)
        return e->active_variant->data<T>();

    if (e->active_emitter)
        return e->active_emitter->variant().value<T*>();

    return d->variant.value<T*>();
}

template <typename T> inline T *dtkComposerTransmitterVariant::data(void)
{
    T *data = this->dataFromEmitter<T>();

    if (e->twinned)
        return data;

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::CopyOnWrite:
        if (this->enableCopy())
            return new T(*data);
        else
            return data;
        break;
    case dtkComposerTransmitter::Copy:
        return new T(*data);
        break;
    case dtkComposerTransmitter::Reference:
        return data;
        break;
    default:
        break;
    };

    return new T();
}

// /////////////////////////////////////////////////////////////////
// Template specializations for atomic types
// /////////////////////////////////////////////////////////////////

template <> inline bool *dtkComposerTransmitterVariant::dataFromEmitter(void)
{
    QVariant::Type emitter_type = this->type();

    QVariant& emitter_variant = this->variant();

    switch (emitter_type) {
    case QVariant::Bool:
        e->value_b = *(emitter_variant.value<bool*>());
        break;
    case QVariant::Double:
        e->value_b = static_cast<bool>(*(emitter_variant.value<qreal*>()));
        break;
    case QVariant::LongLong:
        e->value_b = static_cast<bool>(*(emitter_variant.value<qlonglong*>()));
        break;
    case QVariant::Int:
        e->value_b = static_cast<bool>(*(emitter_variant.value<int*>()));
        break;
    case QVariant::UInt:
        e->value_b = static_cast<bool>(*(emitter_variant.value<uint*>()));
        break;
    case QVariant::ULongLong:
        e->value_b = static_cast<bool>(*(emitter_variant.value<qulonglong*>()));
        break;
    case QVariant::String:
        e->value_b = static_cast<bool>((emitter_variant.value<QString*>())->toLongLong());
        break;
    default:
        break;
    }

    return &(e->value_b);
}

template <> inline bool *dtkComposerTransmitterVariant::data(void)
{
    return this->dataFromEmitter<bool>();
}

template <> inline qlonglong *dtkComposerTransmitterVariant::dataFromEmitter(void)
{
    QVariant::Type emitter_type = this->type();

    QVariant& emitter_variant = this->variant();

    switch (emitter_type) {
    case QVariant::LongLong:
        e->value_i = *(emitter_variant.value<qlonglong*>());
        break;
    case QVariant::Double:
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<qreal*>()));
        break;
    case QVariant::Int:
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<int*>()));
        break;
    case QVariant::UInt:
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<uint*>()));
        break;
    case QVariant::ULongLong:
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<qulonglong*>()));
        break;
    case QVariant::String:
        e->value_i = (emitter_variant.value<QString*>())->toLongLong();
        break;
    case QVariant::Bool:
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<bool*>()));
        break;
    default:
        break;
    }

    return &(e->value_i);
}

template <> inline qlonglong *dtkComposerTransmitterVariant::data(void)
{
    return this->dataFromEmitter<qlonglong>();
}

template <> inline qreal *dtkComposerTransmitterVariant::dataFromEmitter(void)
{
    QVariant::Type emitter_type = this->type();

    QVariant& emitter_variant = this->variant();

    switch (emitter_type) {
    case QVariant::Double:
        e->value_r = *(emitter_variant.value<qreal*>());
        break;
    case QVariant::LongLong:
        e->value_r = static_cast<qreal>(*(emitter_variant.value<qlonglong*>()));
        break;
    case QVariant::Int:
        e->value_r = static_cast<qreal>(*(emitter_variant.value<int*>()));
        break;
    case QVariant::UInt:
        e->value_r = static_cast<qreal>(*(emitter_variant.value<uint*>()));
        break;
    case QVariant::ULongLong:
        e->value_r = static_cast<qreal>(*(emitter_variant.value<qulonglong*>()));
        break;
    case QVariant::String:
        e->value_r = (emitter_variant.value<QString*>())->toDouble();
        break;
    case QVariant::Bool:
        e->value_r = static_cast<qreal>(*(emitter_variant.value<bool*>()));
        break;
    default:
        break;
    }

    return &(e->value_r);
}

template <> inline qreal *dtkComposerTransmitterVariant::data(void)
{
    return this->dataFromEmitter<qreal>();
}

template <> inline QString *dtkComposerTransmitterVariant::dataFromEmitter(void)
{
    QVariant::Type emitter_type = this->type();

    QVariant& emitter_variant = this->variant();

    switch (emitter_type) {
    case QVariant::String:
        e->value_s = *(emitter_variant.value<QString*>());
        break;
    case QVariant::Double:
        e->value_s = QString::number(*(emitter_variant.value<qreal*>()));
        break;
    case QVariant::LongLong:
        e->value_s = QString::number(*(emitter_variant.value<qlonglong*>()));
        break;
    case QVariant::Int:
        e->value_s = QString::number(*(emitter_variant.value<int*>()));
        break;
    case QVariant::UInt:
        e->value_s = QString::number(*(emitter_variant.value<uint*>()));
        break;
    case QVariant::ULongLong:
        e->value_s = QString::number(*(emitter_variant.value<qulonglong*>()));
        break;
    case QVariant::Bool:
        e->value_s = QString::number(static_cast<qreal>(*(emitter_variant.value<bool*>())));
        break;
    default:
        break;
    }

    return &(e->value_s);
}

template <> inline QString *dtkComposerTransmitterVariant::data(void)
{
    return this->dataFromEmitter<QString>();
}

#endif
