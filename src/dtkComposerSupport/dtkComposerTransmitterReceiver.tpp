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

#include <dtkCoreSupport/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty receiver.
/*!
 *
 */
template <typename T> dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterAbstractReceiver(parent)
{
    m_data = NULL;
    d->data_type = qMetaTypeId<T>(m_data);

    active_emitter = NULL;
    active_variant = NULL;
};

//! Destroys the receiver.
/*!
 *
 */
template <typename T> dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{
    m_data = NULL;

    active_emitter = NULL;
    active_variant = NULL;
};

//!
/*!
 *
 */
template <typename T> void dtkComposerTransmitterReceiver<T>::clearData(void)
{
    d->variant.clear();
    d->object = NULL;
    d->container = NULL;
    d->matrix = NULL;

    if (m_data)
        delete m_data;

    m_data = NULL;

}

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> T *dtkComposerTransmitterReceiver<T>::dataFromEmitter(void)
{
    if (active_emitter)
        return active_emitter->data();

    if (active_variant)
        return active_variant->data<T>();

    return NULL;
};

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> T *dtkComposerTransmitterReceiver<T>::data(void)
{
    T *data = this->dataFromEmitter();

    if (!data)
        return NULL;

    switch (this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
        if (this->enableCopy()) {
            if (!m_data) {
                if (dtkTypeInfo<T *>::dtkAbstractObjectPointer)
                    m_data = reinterpret_cast<T *>(reinterpret_cast<dtkAbstractObject *>(data)->clone());
                else
                    m_data = new T(*data);
            } else {
                *m_data = *data;
            }

            return m_data;
        } else {
            return data;
        }

        break;

    case dtkComposerTransmitter::Copy:
        if (!m_data) {
            if (dtkTypeInfo<T *>::dtkAbstractObjectPointer)
                m_data = reinterpret_cast<T *>(reinterpret_cast<dtkAbstractObject *>(data)->clone());
            else
                m_data = new T(*data);
        } else {
            *m_data = *data;
        }

        return m_data;
        break;

    case dtkComposerTransmitter::Reference:
        return data;
        break;

    default:
        return NULL;
        break;
    };

    return NULL;
};

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> T *dtkComposerTransmitterReceiver<T>::constData(void)
{
    if (this->dataTransmission() != dtkComposerTransmitter::Copy) {
        return this->dataFromEmitter();

    } else {
        T *data = this->dataFromEmitter();

        if (!data)
            return NULL;

        if (!m_data) {
            if (dtkTypeInfo<T *>::dtkAbstractObjectPointer)
                m_data = reinterpret_cast<T *>(reinterpret_cast<dtkAbstractObject *>(data)->clone());
            else
                m_data = new T(*data);
        } else {
            *m_data = *data;
        }

        return m_data;
    }

    return NULL;
};

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> dtkAbstractObject *dtkComposerTransmitterReceiver<T>::object(void)
{
    T *data = this->data();

    if (data && dtkTypeInfo<T *>::dtkAbstractObjectPointer)
        return reinterpret_cast<dtkAbstractObject *>(data);

    return NULL;
};

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> dtkMatrixReal *dtkComposerTransmitterReceiver<T>::matrix(void)
{
    T *data = this->data();

    if (data && dtkTypeInfo<T *>::dtkMatrixRealPointer)
        return reinterpret_cast<dtkMatrixReal *>(data);

    return NULL;
};

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> QVariant& dtkComposerTransmitterReceiver<T>::variant(void)
{
    d->variant.setValue(this->data());
    return d->variant;
};

//!
/*!
 *
 */
template <typename T> QVector<T *> dtkComposerTransmitterReceiver<T>::allData(void)
{
    QVector<T *> list;

    int i;
    int count = this->emitters.count();

    for (i = 0; i < count; ++i)
        if (this->emitters.at(i)->active()) {
            list << this->emitters.at(i)->data();
        }

    count = this->variants.count();

    dtkComposerTransmitterVariant *var = NULL;

    for (i = 0; i < count; ++i) {
        var = this->variants.at(i);

        if (var->active()) {
            list << var->data<T>();
        }
    }

    return list;
};

//!
/*!
 *
 */
template <typename T> void dtkComposerTransmitterReceiver<T>::activateEmitter(dtkComposerTransmitter *emitter)
{
    active_emitter = NULL;
    active_variant = NULL;

    foreach (dtkComposerTransmitterEmitter<T> *e, emitters) {
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
template <typename T> void dtkComposerTransmitterReceiver<T>::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    active_emitter = NULL;
    active_variant = NULL;

    foreach (dtkComposerTransmitterVariant *v, variants) {
        if (emitter == v) {
            active_variant = v;
            break;
        }
    }
}

//!
/*!
 *
 */
template <typename T> void dtkComposerTransmitterReceiver<T>::setReady(bool ready)
{
    if (d->ready == ready)
        return;

    d->ready = ready;

    if (this->active_emitter) {
        this->active_emitter->updateCopyCounter(ready);

    } else if (this->active_variant) {
        this->active_variant->updateCopyCounter(ready);

    }
}

//! Returns.
/*!
 *
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::enableCopy(void)
{
    // if (active_emitter)
    //     return active_emitter->enableCopy();

    // if (active_variant)
    //     return active_variant->enableCopy();

    // return false;

    if (this->active_emitter) {
        return this->active_emitter->copyCounterIsGreaterThanOne();
    }

    if (this->active_variant) {
        return this->active_variant->copyCounterIsGreaterThanOne();
    }

    return false;
}

//! Returns.
/*!
 *
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::isEmpty(void) const
{
    if (emitters.isEmpty() && variants.isEmpty())
        return true;

    return false;
};

//! Returns the kind of the transmitter.
/*!
 *
 */
template <typename T> dtkComposerTransmitter::Kind dtkComposerTransmitterReceiver<T>::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
};

template <typename T> QString dtkComposerTransmitterReceiver<T>::kindName(void) const
{
    return "Receiver";
};

//!
/*!
 *
 */
template <typename T> bool dtkComposerTransmitterReceiver<T>::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Emitter) {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitter<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitter<T> *>(transmitter);

            if (!emitters.contains(emitter)) {
                emitters << emitter;
                active_emitter = emitter;
                active_variant = NULL;
                emitter->appendReceiver(this);
                emitter->updateCopyCounter(true);
                return true;
            }
        }

    } else if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (v->dataTypes().isEmpty() && !variants.contains(v)) {
            variants << v;
            active_variant = v;
            active_emitter = NULL;
            v->appendReceiver(this);
            v->updateCopyCounter(true);
            return true;
        } else {
            foreach (int t, v->dataTypes()) {
                if (t == this->dataType() && !variants.contains(v)) {
                    variants << v;
                    active_variant = v;
                    active_emitter = NULL;
                    v->appendReceiver(this);
                    v->updateCopyCounter(true);
                    return true;
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
template <typename T> bool dtkComposerTransmitterReceiver<T>::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {

        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);

        ok = variants.removeOne(v);

        if (v == active_variant) {

            active_variant = NULL;

            foreach (dtkComposerTransmitterVariant *var, variants) {
                if (var->active())
                    active_variant = var;
            }

            if (!active_variant) {
                foreach (dtkComposerTransmitterEmitter<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }
            }
        }

    } else {

        if (this->dataType() == transmitter->dataType()) {

            dtkComposerTransmitterEmitter<T> *emitter = reinterpret_cast<dtkComposerTransmitterEmitter<T> *>(transmitter);

            ok = emitters.removeOne(emitter);

            if (emitter == active_emitter) {

                active_emitter = NULL;

                foreach (dtkComposerTransmitterEmitter<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }

                if (!active_emitter) {
                    foreach (dtkComposerTransmitterVariant *var, variants) {
                        if (var->active())
                            active_variant = var;
                    }
                }
            }
        }
    }

    if (ok) {
        transmitter->updateCopyCounter(false);
    }

    return ok;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVector implementation
// /////////////////////////////////////////////////////////////////

#include <dtkContainerSupport/dtkContainerVectorWrapper.h>

template <typename T> inline dtkComposerTransmitterReceiverVector<T>::dtkComposerTransmitterReceiverVector(dtkComposerNode *parent) : dtkComposerTransmitterAbstractReceiver(parent)
{
    m_vector = NULL;
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper *>(0));

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
    d->object = NULL;
    d->matrix = NULL;

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

    switch (this->dataTransmission()) {
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

//! Returns the data as a modifiable reference.
/*!
 *
 */
template <typename T> dtkAbstractObject *dtkComposerTransmitterReceiverVector<T>::object(void)
{
    return this->container();
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
template <typename T> QVariant& dtkComposerTransmitterReceiverVector<T>::variant(void)
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

    foreach (dtkComposerTransmitterEmitterVector<T> *e, emitters) {
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

    foreach (dtkComposerTransmitterVariant *v, variants) {
        if (emitter == v) {
            active_variant = v;
            break;
        }
    }
}

template <typename T> void dtkComposerTransmitterReceiverVector<T>::setReady(bool ready)
{
    if (ready == d->ready)
        return;

    d->ready = ready;

    if (this->active_emitter) {
        this->active_emitter->updateCopyCounter(ready);

    } else if (this->active_variant) {
        this->active_variant->updateCopyCounter(ready);

    }
}

//! Returns.
/*!
 *
 */
template <typename T> bool dtkComposerTransmitterReceiverVector<T>::enableCopy(void)
{
    // if (active_emitter)
    //     return active_emitter->enableCopy();

    // if (active_variant)
    //     return active_variant->enableCopy();

    // return false;

    if (this->active_emitter) {
        return this->active_emitter->copyCounterIsGreaterThanOne();
    }

    if (this->active_variant) {
        return this->active_variant->copyCounterIsGreaterThanOne();
    }

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
                emitter->updateCopyCounter(true);
                return true;
            }
        }

    } else if (transmitter->kind() == dtkComposerTransmitter::Variant) {

        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);

        if (v->dataTypes().isEmpty() && !variants.contains(v)) {
            variants << v;
            active_variant = v;
            active_emitter = NULL;
            v->appendReceiver(this);
            v->updateCopyCounter(true);
            return true;
        } else {
            foreach (int t, v->dataTypes()) {
                if (t == this->dataType() && !variants.contains(v)) {
                    variants << v;
                    active_variant = v;
                    active_emitter = NULL;
                    v->appendReceiver(this);
                    v->updateCopyCounter(true);
                    return true;
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

            foreach (dtkComposerTransmitterVariant *var, variants) {
                if (var->active())
                    active_variant = var;
            }

            if (!active_variant) {
                foreach (dtkComposerTransmitterEmitterVector<T> *em, emitters) {
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

                foreach (dtkComposerTransmitterEmitterVector<T> *em, emitters) {
                    if (em->active())
                        active_emitter = em;
                }

                if (!active_emitter) {
                    foreach (dtkComposerTransmitterVariant *var, variants) {
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
