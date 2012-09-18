/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 16:38:45 2012 (+0200)
 *           By: tkloczko
 *     Update #: 701
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerTransmitterVariant_p.h"

#include <dtkContainer>

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

#include <dtkDistributed/dtkDistributedMessage.h>

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMath.h>

// /////////////////////////////////////////////////////////////////
// Template specializations for atomic types
// /////////////////////////////////////////////////////////////////

template <> bool *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();

    if (emitter_variant.canConvert<bool>()) {
        e->value_b = emitter_variant.value<bool>();

    } else {
        int emitter_type = this->dataType();

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
            e->value_b = false;
            return NULL;
            break;
        }
    }

    return &(e->value_b);
}

template <> qlonglong *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();

    if (emitter_variant.canConvert<qlonglong>()) {
        e->value_i = emitter_variant.value<qlonglong>();

    } else {
        int emitter_type = this->dataType();

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
            e->value_i = 0;
            return NULL;
            break;
        }
    }

    return &(e->value_i);
}

template <> qreal *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();

    if (emitter_variant.canConvert<qreal>()) {
        e->value_r = emitter_variant.value<qreal>();

    } else {
        int emitter_type = this->dataType();
        
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
        case uint(QVariant::ULongLong):
            e->value_r = static_cast<qreal>(*(emitter_variant.value<qulonglong*>()));
            break;
        case QVariant::String:
            e->value_r = (emitter_variant.value<QString*>())->toDouble();        
            break;
        case QVariant::Bool:
            e->value_r = static_cast<qreal>(*(emitter_variant.value<bool*>()));
            break;
        default:
            e->value_r = 0.0;
            return NULL;
            break;
        }
    }

    return &(e->value_r);
}

template <> QString *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();

    if (emitter_variant.canConvert<QString>()) {
        e->value_s = emitter_variant.value<QString>();

    } else {
        int emitter_type = this->dataType();

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
            e->value_s = QString();
            return NULL;
            break;
        }
    }

    return &(e->value_s);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    e->twin = NULL;
    e->twinned = false;
    e->already_ask = false;

    e->m_variant.clear();
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete e;

    e = NULL;
}

//! Puts \a data into the variant transmitter which then plays the
//! role of an emitter.
/*! 
 *  This methods resets the container of the transmiter. This is quite
 *  important because it enables to test whether the variant
 *  transmitter contains a container or not using isReset() method
 *  from the dtkAbstractContainerWrapper class.
 *  
 *  
 */

void dtkComposerTransmitterVariant::setData(const QVariant& data)
{
    d->data_type = data.userType();
    d->variant = data;
    if (d->container) {
        delete d->container;
        d->container = NULL;
    }
}

void dtkComposerTransmitterVariant::setData(dtkAbstractContainerWrapper *data)
{
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper*>(0));
    d->container = data;
    d->variant.setValue(d->container);
}

void dtkComposerTransmitterVariant::setDataFrom(dtkComposerTransmitterVariant *source)
{
    d->data_type = source->dataType();
    d->variant = source->variant();
    if (d->container) {
        delete d->container;
    }
    d->container = source->container();
}

void dtkComposerTransmitterVariant::setDataFrom(dtkDistributedMessage *msg)
{
    // if (msg->type() == "double") {

    //     double *data = reinterpret_cast<double*>(msg->content().data());
    //     this->setTwinned(false);
    //     this->setData(data);
    //     this->setTwinned(true);

    // } else if (msg->type() == "qlonglong") {

    //     qlonglong *data = reinterpret_cast<qlonglong*>(msg->content().data());
    //     this->setTwinned(false);
    //     this->setData(data);
    //     this->setTwinned(true);

    // } else if (msg->type() == "qstring") {

    //     this->setTwinned(false);
    //     this->setData(new QString(msg->content()));
    //     this->setTwinned(true);

    // } else if (msg->type() == "dtkVectorReal") {

    //     if (msg->size() > 0) {
    //         QByteArray array = msg->content();
    //         int size;
    //         QDataStream stream(&array, QIODevice::ReadOnly);
    //         stream >> size;
    //         dtkVectorReal *v = new dtkVectorReal(size);

    //         for (int i=0; i< size; i++)
    //             stream >> *(v[i]);

    //         this->setTwinned(false);
    //         this->setData(v);
    //         this->setTwinned(true);

    //         dtkDebug() << "received dtkVectorReal, set data in transmitter; size is " << size;

    //     } else
    //         dtkWarn() << "warning: no content in dtkVectorReal transmitter";

    // } else if (msg->type() == "dtkVector3DReal") {

    //     if (msg->size() > 0) {
    //         dtkVector3DReal *v = new dtkVector3D<qreal>();

    //         QDataStream stream(&(msg->content()), QIODevice::ReadOnly);
    //         stream >> *v[0];
    //         stream >> *v[1];
    //         stream >> *v[2];

    //         this->setTwinned(false);
    //         this->setData(v);
    //         this->setTwinned(true);

    //         dtkDebug() << "received dtkVector3DReal, set data in transmitter" << *v[0] << *v[1] << *v[2];

    //     } else
    //         dtkWarn() << "warning: no content in dtkVector3DReal transmitter";

    // } else if (msg->type() == "dtkQuaternionReal") {

    //     if (msg->size() > 0) {
    //         dtkQuaternionReal q = new dtkQuaternion<qreal>();

    //         QDataStream stream(&(msg->content()), QIODevice::ReadOnly);
    //         stream >> *q[0];
    //         stream >> *q[1];
    //         stream >> *q[2];
    //         stream >> *q[3];

    //         this->setTwinned(false);
    //         this->setData(q);
    //         this->setTwinned(true);

    //         dtkDebug() << "received dtkQuaternionReal, set data in transmitter" << *q[0] << *q[1] << *q[2] << *q[3];

    //     } else
    //         dtkWarn() << "warning: no content in dtkQuaternionReal transmitter";

    // } else { // assume a dtkAbstractData

    //     dtkDebug() << "received" <<  msg->type() << ", deserialize";
    //     QString type ;
    //     QString transmitter_type;
    //     if (msg->type().section('/',1,1).isEmpty()) {
    //         type = msg->type();
    //         transmitter_type = type;
    //     } else {
    //         transmitter_type = msg->type().section('/',0,0);
    //         type = msg->type().section('/',1,1);
    //     }

    //     dtkDebug() << "type:" << type;
    //     dtkDebug() << "transmitter_type:" << transmitter_type;
    //     if (msg->size() > 0) {
    //         dtkAbstractData *data;
    //         data = dtkAbstractDataFactory::instance()->create(type)->deserialize(msg->content());
    //         if (!data) {
    //             dtkError() << "Deserialization failed";
    //         } else {
    //             dtkDebug() << "set dtkAbstractData in transmitter, size is" << msg->size();
    //             if (transmitter_type == "dtkAbstractData") {
    //                 this->setData(data);
    //             } else {
    //                 // this->setData(data->toVariant(data));
    //             }
    //         }
    //     } else
    //         dtkWarn() << "warning: no content in dtkAbstractData transmitter";
    // }
}

QVariant& dtkComposerTransmitterVariant::variant(void)
{
    if (e->twinned)
        return d->variant;

    if (e->active_variant)
        return e->active_variant->variant();

    if (e->active_emitter)
        return e->active_emitter->variant();

    return d->variant;
}

dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::containerFromEmitter(void)
{
    if (e->twinned)
        return d->container;

    if (e->active_variant)
        return e->active_variant->container();
    
    if (e->active_emitter)
        return e->active_emitter->container();

    return d->container;
}

dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::container(void)
{
    dtkAbstractContainerWrapper *container = this->containerFromEmitter();

    if (!container)
        return NULL;

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::CopyOnWrite:
        if (this->enableCopy())
            return container->clone();
        else
            return container;
        break;
    case dtkComposerTransmitter::Copy:
        return container->clone();
        break;
    case dtkComposerTransmitter::Reference:
        return container;
        break;
    default:
        break;
    };

    return NULL;   
}

QVariantList dtkComposerTransmitterVariant::allData(void)
{
    QVariantList list;

    if (e->twinned) {

        list << d->variant;

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; i++)
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->variant();
            }

        count = e->variants.count();

        for(int i = 0; i < count; i++)
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->variant();
            }

    }

    return list;
}

int dtkComposerTransmitterVariant::dataType(void)
{
    if (e->twinned)
        return d->data_type;

    if (e->active_variant)
        return e->active_variant->dataType();

    if (e->active_emitter)
        return e->active_emitter->dataType();

    return d->data_type;
}

QString dtkComposerTransmitterVariant::dataIdentifier(void)
{
    if (dtkAbstractObject *o = d->variant.value<dtkAbstractObject*>())
        return o->identifier();

    return QString(QMetaType::typeName(this->dataType()));
}

QString dtkComposerTransmitterVariant::dataDescription(void)
{
    if (dtkAbstractObject *o = d->variant.value<dtkAbstractObject*>())
        return o->description();

    QString address;
    QTextStream addressStream (&address);
    addressStream << (d->variant.value<void*>());

    return address;
}

QStringList dtkComposerTransmitterVariant::allDataIdentifier(void)
{
    QStringList list;

    if (e->twinned) {

        list << QString(QMetaType::typeName(d->data_type));

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; ++i) {
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->dataIdentifier();
            }
        }

        count = e->variants.count();

        for(int i = 0; i < count; ++i) {
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->dataIdentifier();
            }
        }
    }

    return list;
}

QStringList dtkComposerTransmitterVariant::allDataDescription(void)
{
    QStringList list;

    if (e->twinned) {

        QString address;
        QTextStream addressStream (&address);
        addressStream << (d->variant.value<void*>());

        list << address;

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; ++i) {
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->dataDescription();
            }
        }

        count = e->variants.count();

        for(int i = 0; i < count; ++i) {
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->dataDescription();
            }
        }
    }

    return list;
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitterVariant::activateEmitter(dtkComposerTransmitter *emitter)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    foreach(dtkComposerTransmitter *em, e->emitters) {
        if (emitter == em) {
            e->active_emitter = emitter;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitterVariant::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;
    
    foreach(dtkComposerTransmitterVariant *v, e->variants) {
        if (emitter == v) {
            e->active_variant = v;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::enableCopy(void)
{
    if (e->twinned) {
        if (e->already_ask)/// ATENTION A TEST\ER
            return false;
        else {
            e->already_ask = true;
            if (d->receivers.count() > 1)
                return true;
        }
    }

    if (e->active_variant)
        return e->active_variant->enableCopy();

    if (e->active_emitter)
        return e->active_emitter->enableCopy();

    return (d->receivers.count() > 1);
}

void dtkComposerTransmitterVariant::reset(void)
{
    e->already_ask = false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::isEmpty(void) const
{
    if (e->emitters.isEmpty() && e->variants.isEmpty())
        return true;

    return false;
};

void dtkComposerTransmitterVariant::setTwin(dtkComposerTransmitterVariant *twin)
{
    e->twin = twin;
}

dtkComposerTransmitterVariant *dtkComposerTransmitterVariant::twin(void)
{
    return e->twin;
}
    
void dtkComposerTransmitterVariant::setTwinned(bool twinned)
{
    e->twinned = twinned;
}

//! Returns.
/*! 
 *  
 */
dtkComposerTransmitter::Kind dtkComposerTransmitterVariant::kind(void) const
{
    return dtkComposerTransmitter::Variant;
}

QString dtkComposerTransmitterVariant::kindName(void) const
{
    return "Variant";
}

void dtkComposerTransmitterVariant::setDataTypes(const QList<int>& data_types)
{
    e->data_types = data_types;
}

QList<int> dtkComposerTransmitterVariant::dataTypes(void)
{
    return e->data_types;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Variant) {
        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (e->data_types.isEmpty() || v->dataTypes().isEmpty()) {
            if (!e->variants.contains(v)) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;
            }
        } else {
            foreach(int t, v->dataTypes()) {
                if (!e->variants.contains(v) && e->data_types.contains(t)) {
                    e->variants << v;
                    e->active_variant = v;
                    e->active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
        }
    }

    if (e->data_types.isEmpty() || e->data_types.contains(transmitter->dataType())) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            e->active_emitter = transmitter;
            e->active_variant = NULL;
            transmitter->appendReceiver(this);
            return true;
        }
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {
        
        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);
        
        ok = e->variants.removeOne(v);

        if (v == e->active_variant) {

            e->active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, e->variants) {
                if (var->active())
                    e->active_variant = var;
            }
            
            if (!e->active_variant) {
                foreach(dtkComposerTransmitter *em, e->emitters) {
                    if (em->active())
                        e->active_emitter = em;
                }
            }
        }
            
    } else {

        ok = e->emitters.removeOne(transmitter);

        if (transmitter == e->active_emitter) {

            e->active_emitter = NULL;

            foreach(dtkComposerTransmitter *em, e->emitters) {
                if (em->active())
                    e->active_emitter = em;
            }

            if (!e->active_emitter) {
                foreach(dtkComposerTransmitterVariant *var, e->variants) {
                    if (var->active())
                        e->active_variant = var;
                }
            }            

        }
    }    
    
    return ok ;
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}
