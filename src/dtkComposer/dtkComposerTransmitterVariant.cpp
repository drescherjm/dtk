/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Aug  7 16:13:11 2012 (+0200)
 *           By: tkloczko
 *     Update #: 567
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
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    e->twin = NULL;
    e->twinned = false;
    e->already_ask = false;
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
    d->type = data;
    d->variant = data;
    d->container->reset();
}

void dtkComposerTransmitterVariant::setData(dtkAbstractContainerWrapper *data)
{
    dtkAbstractContainerWrapper w;
    d->type.setValue(w);
    d->container = data;
    d->variant.setValue(d->container);
}

void dtkComposerTransmitterVariant::setDataFromMsg(dtkDistributedMessage *msg)
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

QVariant& dtkComposerTransmitterVariant::variantFromEmitter(void)
{
    if (e->twinned)
        return d->variant;

    if (e->active_variant)
        return e->active_variant->variant();

    if (e->active_emitter)
        return e->active_emitter->variant();

    return d->variant;
}

QVariant& dtkComposerTransmitterVariant::variant(void)
{
    return this->variantFromEmitter();
}

dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::container(void)
{
    if (e->twinned)
        return d->container;

    if (e->active_variant)
        return e->active_variant->container();
    
    if (e->active_emitter)
        return e->active_emitter->container();

    return d->container;    
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

QVariant::Type dtkComposerTransmitterVariant::type(void) const
{
    if (e->twinned)
        return d->type.type();

    if (e->active_variant)
        return e->active_variant->type();
    
    if (e->active_emitter)
        return e->active_emitter->type();

    return d->type.type();
}

QString dtkComposerTransmitterVariant::typeName(void) const
{
    if (e->twinned)
        return d->type.typeName();

    if (e->active_variant)
        return e->active_variant->typeName();
    
    if (e->active_emitter)
        return e->active_emitter->typeName();

    return d->type.typeName();
}

void dtkComposerTransmitterVariant::setTypes(QList<QVariant::Type> types)
{
    e->types = types;
}

QList<QVariant::Type> dtkComposerTransmitterVariant::types(void)
{
    return e->types;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Variant) {
        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (e->types.isEmpty() || v->types().isEmpty()) {
            if (!e->variants.contains(v)) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;
            }
        } else {
            foreach(QVariant::Type t, v->types()) {
                if (!e->variants.contains(v) && e->types.contains(t)) {
                    e->variants << v;
                    e->active_variant = v;
                    e->active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
        }
    }

    if (e->types.isEmpty() || e->types.contains(transmitter->type())) {
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
