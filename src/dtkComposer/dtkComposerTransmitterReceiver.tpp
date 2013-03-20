/* dtkComposerTransmitterReceiver.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 12:56:04 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERRECEIVER_TPP
#define DTKCOMPOSERTRANSMITTERRECEIVER_TPP

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterVariant.h"

#include "dtkComposerTransmitterHandler.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiverBase<T>::dtkComposerTransmitterReceiverBase(dtkComposerNode *parent) : dtkComposerTransmitterAbstractReceiver(parent)
{
    this->active_emitter = NULL;
    this->active_variant = NULL;
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiverBase<T>::~dtkComposerTransmitterReceiverBase(void)
{
    this->active_emitter = NULL;
    this->active_variant = NULL;
};

//! 
/*! 
 *  
 */
template <typename T> void dtkComposerTransmitterReceiverBase<T>::activateEmitter(dtkComposerTransmitter *emitter)
{
    this->active_emitter = NULL;
    this->active_variant = NULL;

    foreach(dtkComposerTransmitterEmitter<T> *e, this->emitters) {
        if (emitter == static_cast<dtkComposerTransmitter *>(e)) {
            this->active_emitter = e;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
template <typename T> void dtkComposerTransmitterReceiverBase<T>::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    this->active_emitter = NULL;
    this->active_variant = NULL;
    
    foreach(dtkComposerTransmitterVariant *v, this->variants) {
        if (emitter == v) {
            this->active_variant = v;
            break;
        }
    }
}

//! Returns.
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverBase<T>::enableCopy(void)
{
    if (this->active_emitter)
        return this->active_emitter->enableCopy();

    if (this->active_variant)
        return this->active_variant->enableCopy();

    return false;
}

//! Returns.
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverBase<T>::isEmpty(void) const
{
    if (this->emitters.isEmpty() && this->variants.isEmpty())
        return true;

    return false;
};

//! Returns the kind of the transmitter.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiverBase<T>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
};

template <typename T> QString dtkComposerTransmitterReceiverBase<T>::kindName(void) const
{
    return "Receiver";
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverBase<T>::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Emitter) {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitter<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitter<T> *>(transmitter);

            if (!emitters.contains(emitter)) {
                this->emitters << emitter;
                this->active_emitter = emitter;
                this->active_variant = NULL;
                emitter->appendReceiver(this);
                return true;
            }
        }

    } else if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (!this->variants.contains(v)) {

            if (v->dataTypes().isEmpty()) {
                this->variants << v;
                this->active_variant = v;
                this->active_emitter = NULL;
                v->appendReceiver(this);
                return true;

            } else {
                foreach(const dtkComposerType *t, v->dataTypes()) {
                    if (*t == (this->dataType())) {
                        this->variants << v;
                        this->active_variant = v;
                        this->active_emitter = NULL;
                        v->appendReceiver(this);
                        return true;
                    }
                }
            }
        }
    }

    return false;
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverBase<T>::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);

        ok = this->variants.removeOne(v);

        if (v == this->active_variant) {

            this->active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, this->variants) {
                if (var->active())
                    this->active_variant = var;
            }

            if (!this->active_variant) {
                foreach(dtkComposerTransmitterEmitter<T> *em, this->emitters) {
                    if (em->active())
                        this->active_emitter = em;
                }
            }
        }

    } else {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitter<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitter<T> *>(transmitter);

            ok = this->emitters.removeOne(emitter);

            if (emitter == this->active_emitter) {

                this->active_emitter = NULL;

                foreach(dtkComposerTransmitterEmitter<T> *em, this->emitters) {
                    if (em->active())
                        this->active_emitter = em;
                }

                if (!this->active_emitter) {
                    foreach(dtkComposerTransmitterVariant *var, this->variants) {
                        if (var->active())
                            this->active_variant = var;
                    }
                }
            }
        }
    }

    return ok;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase<T>(parent)
{
    this->m_data = T();
    d->data_type = dtkComposerTypeInfo<T>::type();
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{
};

//! 
/*!  
 *  
 */
template <typename T> void dtkComposerTransmitterReceiver<T>::clearData(void)
{
    d->variant.clear();

    this->m_data = T();
    
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T& dtkComposerTransmitterReceiver<T>::dataFromEmitter(void)
{
    if (this->active_emitter)
        this->m_data = this->active_emitter->data();
    
    if (this->active_variant)
        this->m_data = this->active_variant->template data<T>();

    return this->m_data;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T& dtkComposerTransmitterReceiver<T>::data(void)
{
    return this->dataFromEmitter();
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T& dtkComposerTransmitterReceiver<T>::constData(void)
{   
    return this->dataFromEmitter();
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> dtkComposerVariant& dtkComposerTransmitterReceiver<T>::variant(void)
{
    d->variant.setValue(this->data());
    return d->variant;
};

//! 
/*! 
  *  
 */
template <typename T> QVector<T> dtkComposerTransmitterReceiver<T>::allData(void)
{
    QVector<T> list;

    int i;
    int count = this->emitters.count();

    for(i = 0; i < count; ++i)
        if (this->emitters.at(i)->active()) {
            list << this->emitters.at(i)->data();
        }

    count = this->variants.count();

    dtkComposerTransmitterVariant *var = NULL;

    for(i = 0; i < count; ++i) {
        var = this->variants.at(i);
        if (var->active()) {
            list << var->data<T>();
        }
    }

    return list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T*>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase<T*>(parent)
{
    this->m_data = NULL;
    d->data_type = dtkComposerTypeInfo<T*>::type();
};

//! Destroys the receiver.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitterReceiver<T*>::~dtkComposerTransmitterReceiver(void)
{
    this->m_data = NULL;
};

//! 
/*!  
 *  
 */
template <typename T> void dtkComposerTransmitterReceiver<T*>::clearData(void)
{
    d->variant.clear();

    this->m_data = NULL;
    
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T* dtkComposerTransmitterReceiver<T*>::dataFromEmitter(void)
{
    if (this->active_emitter)
        return this->active_emitter->data();
    
    if (this->active_variant)
        return this->active_variant->template data<T*>();

    return this->m_data;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T* dtkComposerTransmitterReceiver<T*>::data(void)
{
    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
        return dtkComposerTransmitterHandler<T, dtkComposerTypeInfo<T*>::isObjectPointer>::copyData(this->dataFromEmitter(), m_data, this->enableCopy());
        break;
    case dtkComposerTransmitter::Reference:
        return dtkComposerTransmitterHandler<T, dtkComposerTypeInfo<T*>::isObjectPointer>::copyData(this->dataFromEmitter(), m_data, false);
        break;
    case dtkComposerTransmitter::Copy:
        return dtkComposerTransmitterHandler<T, dtkComposerTypeInfo<T*>::isObjectPointer>::copyData(this->dataFromEmitter(), m_data, true);
        break;
    default:
        return this->dataFromEmitter();
    }
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> T* dtkComposerTransmitterReceiver<T*>::constData(void)
{   
    bool copy = (this->dataTransmission() == dtkComposerTransmitter::Copy);

    return dtkComposerTransmitterHandler<T, dtkComposerTypeInfo<T*>::isObjectPointer>::copyData(this->dataFromEmitter(), m_data, copy);
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> dtkComposerVariant& dtkComposerTransmitterReceiver<T*>::variant(void)
{
    d->variant.setValue(this->data());
    return d->variant;
};

//! 
/*! 
 *  
 */
template <typename T> QVector<T*> dtkComposerTransmitterReceiver<T*>::allData(void)
{
    QVector<T*> list;

    int i;
    int count = this->emitters.count();

    for(i = 0; i < count; ++i)
        if (this->emitters.at(i)->active()) {
            list << this->emitters.at(i)->data();
        }

    count = this->variants.count();

    dtkComposerTransmitterVariant *var = NULL;

    for(i = 0; i < count; ++i) {
        var = this->variants.at(i);
        if (var->active()) {
            list << var->data<T*>();
        }
    }

    return list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVector implementation
// /////////////////////////////////////////////////////////////////

#include <dtkContainer/dtkContainerVectorWrapper.h>

template <typename T> inline dtkComposerTransmitterReceiverVector<T>::dtkComposerTransmitterReceiverVector(dtkComposerNode *parent) : dtkComposerTransmitterAbstractReceiver(parent)
{
    m_vector= NULL;
    d->data_type = dtkComposerTypeInfo<dtkContainerVector<T>*>::type();

    active_emitter = NULL;
    active_variant = NULL;
};

template <typename T> inline dtkComposerTransmitterReceiverVector<T>::~dtkComposerTransmitterReceiverVector(void)
{

};

//! 
/*!  
 *  
 */
template <typename T> void dtkComposerTransmitterReceiverVector<T>::clearData(void)
{
    d->variant.clear();

    if (d->container)
        delete d->container;
    d->container = NULL;

    if (m_vector)
        delete m_vector;
    m_vector = NULL;
};

template <typename T> dtkContainerVector<T> *dtkComposerTransmitterReceiverVector<T>::dataFromEmitter(void)
{
    if (active_emitter)
        return active_emitter->data();

    if (active_variant)
        return active_variant->container()->vector<T>();

    return NULL;
};

template <typename T> dtkContainerVector<T> *dtkComposerTransmitterReceiverVector<T>::data(void)
{
    dtkContainerVector<T> *vector = this->dataFromEmitter();

    if (!vector)
        return NULL;

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
        if (this->enableCopy()) {
            if (!m_vector)
                m_vector = vector->clone();
            else 
                *(m_vector) = *vector;
            return m_vector;
        } else {
            return vector;
        }
        break;
    case dtkComposerTransmitter::Copy:
        if (!m_vector)
            m_vector = vector->clone();
        else 
            *(m_vector) = *vector;
        return m_vector;
        break;
    case dtkComposerTransmitter::Reference:
        return vector;
        break;
    default:
        break;
    };
    
    return NULL;
};

template <typename T> dtkContainerVector<T> *dtkComposerTransmitterReceiverVector<T>::constData(void)
{
    if (this->dataTransmission() != dtkComposerTransmitter::Copy) {
        return this->dataFromEmitter();

    } else {
        dtkContainerVector<T> *vector = this->dataFromEmitter();
        if (!vector)
            return NULL;
        if (!m_vector)
            m_vector = vector->clone();
        else 
            *(m_vector) = *vector;
        return m_vector;
    }
    
    return NULL;
};

//! 
/*! 
 *  
 */
template <typename T> dtkAbstractContainerWrapper *dtkComposerTransmitterReceiverVector<T>::container(void)
{
    dtkContainerVector<T> *vector = this->data();

    if (!vector)
        return NULL;

    if (!d->container)
        d->container = new dtkContainerVectorWrapper<T>(vector);
    else
        d->container->setVector(vector);

    return d->container;
};

//! 
/*! 
 *  
 */
template <typename T> dtkComposerVariant& dtkComposerTransmitterReceiverVector<T>::variant(void)
{
    d->variant.setValue(this->container());
    return d->variant;
};

//! 
/*! 
 *  
 */
template <typename T> void dtkComposerTransmitterReceiverVector<T>::activateEmitter(dtkComposerTransmitter *emitter)
{
    active_emitter = NULL;
    active_variant = NULL;

    foreach(dtkComposerTransmitterEmitterVector<T> *e, emitters) {
        if (emitter == static_cast<dtkComposerTransmitter *>(e)) {
            active_emitter = e;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
template <typename T> void dtkComposerTransmitterReceiverVector<T>::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    active_emitter = NULL;
    active_variant = NULL;
    
    foreach(dtkComposerTransmitterVariant *v, variants) {
        if (emitter == v) {
            active_variant = v;
            break;
        }
    }
}

//! Returns.
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverVector<T>::enableCopy(void)
{
    if (active_emitter)
        return active_emitter->enableCopy();

    if (active_variant)
        return active_variant->enableCopy();
    
    return false;
}
    
//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverVector<T>::isEmpty(void) const
{
    if (emitters.isEmpty() && variants.isEmpty())
        return true;

    return false;
};

//! Returns the kind of the transmitter.
/*! 
 *  
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiverVector<T>::kind(void) const
{
    return dtkComposerTransmitter::ReceiverVector;
};

template <typename T> QString dtkComposerTransmitterReceiverVector<T>::kindName(void) const
{
    return "ReceiverContainer";
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverVector<T>::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == dtkComposerTransmitter::EmitterVector) {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitterVector<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitterVector<T> *>(transmitter);

            if (!emitters.contains(emitter)) {

                emitters << emitter;
                active_emitter = emitter;
                active_variant = NULL;
                emitter->appendReceiver(this);
                return true;
            }
        }

    } else if (transmitter->kind() == dtkComposerTransmitter::Variant) {

        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (!variants.contains(v)) {

            if (v->dataTypes().isEmpty()) {
                variants << v;
                active_variant = v;
                active_emitter = NULL;
                v->appendReceiver(this);
                return true;

            } else {
                foreach(const dtkComposerType *t, v->dataTypes()) {
                    if (*t == this->dataType()) {
                        variants << v;
                        active_variant = v;
                        active_emitter = NULL;
                        v->appendReceiver(this);
                        return true;
                    }
                }
            }
        }
    }

    return false;
};

//! 
/*! 
 *  
 */
template <typename T> bool dtkComposerTransmitterReceiverVector<T>::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == dtkComposerTransmitter::Variant) {

        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);
        
        ok = variants.removeOne(v);
        
        if (v == active_variant) {
            
            active_variant = NULL;
            
            foreach(dtkComposerTransmitterVariant *var, variants) {
                if (var->active())
                    active_variant = var;
            }
            
            if (!active_variant) {
                foreach(dtkComposerTransmitterEmitterVector<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }
            }
        }
            
    } else {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitterVector<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitterVector<T> *>(transmitter);

            ok = emitters.removeOne(emitter);

            if (emitter == active_emitter) {

                active_emitter = NULL;

                foreach(dtkComposerTransmitterEmitterVector<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }

                if (!active_emitter) {
                    foreach(dtkComposerTransmitterVariant *var, variants) {
                        if (var->active())
                            active_variant = var;
                    }
                }
            }
        }
    }

    return ok;
};

#endif
