/* dtkComposerTransmitterReceiver.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 13:53:01 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 23:01:13 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 123
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter_p.h"

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase implementation
// /////////////////////////////////////////////////////////////////

void dtkComposerTransmitterReceiverBase::clearData(void)
{
    d->variant.clear();
}

bool dtkComposerTransmitterReceiverBase::enableCopy(void)
{
    if (this->active_emitter)
        return active_emitter->enableCopy();

    return false;
}

void dtkComposerTransmitterReceiverBase::activateEmitter(dtkComposerTransmitter *emitter)
{
    this->active_emitter = NULL;

    foreach(dtkComposerTransmitterEmitterBase *e, this->emitters) {
        if (emitter == static_cast<dtkComposerTransmitter *>(e)) {
            this->active_emitter = e;
            break;
        }
    }
}

bool dtkComposerTransmitterReceiverBase::isEmpty(void) const
{
    return this->emitters.isEmpty();
}

QVariant& dtkComposerTransmitterReceiverBase::variant(void)
{
    if (this->active_emitter)
	return this->active_emitter->variant();

    return d->variant;
}

QVariantList dtkComposerTransmitterReceiverBase::allData(void)
{
    QVariantList list;

    int count = this->emitters.count();
    dtkComposerTransmitter *e = NULL;

    for(int i = 0; i < count; ++i) {
	e = this->emitters.at(i);
	if (e->active()) {
	    list << e->variant();
	}
    }

    return list;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a receiver.
/*! 
 *  Initialize the type of the receiver and the variant that it contains.
 */
template <typename T> dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{
    d->type = qMetaTypeId<T>(reinterpret_cast<T *>(0));
    d->variant = QVariant(d->type, 0);
}

template <typename T> dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{

}

template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiver<T>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
}

template <typename T> QString dtkComposerTransmitterReceiver<T>::kindName(void) const
{
    return "Receiver";
}

template <typename T> T dtkComposerTransmitterReceiver<T>::data(void)
{
    return dtkComposerTransmitterReceiverBase::variant().value<T>();
}

template <typename T> T dtkComposerTransmitterReceiver<T>::constData(void)
{
    return dtkComposerTransmitterReceiverBase::variant().value<T>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a receiver.
/*! 
 *  Initialize the type of the receiver and the variant that it contains.
 */
template <typename T> dtkComposerTransmitterReceiver<T*>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{
    d->type = qMetaTypeId<T*>(reinterpret_cast<T **>(0));
    d->variant = QVariant(d->type, 0);
}

template <typename T> dtkComposerTransmitterReceiver<T*>::~dtkComposerTransmitterReceiver(void)
{

}

template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiver<T*>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
}

template <typename T> QString dtkComposerTransmitterReceiver<T*>::kindName(void) const
{
    return "Receiver";
}

template <typename T> T* dtkComposerTransmitterReceiver<T*>::data(void)
{
    const QVariant& source = dtkComposerTransmitterReceiverBase::variant();

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	return dtkComposerTransmitterHandler<T, IsPointerToTypeDerivedFromCoreObject<T*>::Value>::copyData(source, d->variant, this->enableCopy());
	break;
    case dtkComposerTransmitter::Reference:
	return dtkComposerTransmitterHandler<T, IsPointerToTypeDerivedFromCoreObject<T*>::Value>::copyData(source, d->variant, false);       
	break;
    case dtkComposerTransmitter::Copy:
	return dtkComposerTransmitterHandler<T, IsPointerToTypeDerivedFromCoreObject<T*>::Value>::copyData(source, d->variant, true);
	break;
    default:
        return source.value<T*>();
    }
}

template <typename T> T* dtkComposerTransmitterReceiver<T*>::constData(void)
{
    const QVariant& source = dtkComposerTransmitterReceiverBase::variant();

    bool enable_copy = (this->dataTransmission() == dtkComposerTransmitter::Copy);

    return dtkComposerTransmitterHandler<T, IsPointerToTypeDerivedFromCoreObject<T*>::Value>::copyData(source, d->variant, enable_copy);
}

