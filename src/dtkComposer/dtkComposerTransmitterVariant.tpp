/* dtkComposerTransmitterVariant.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:31:25 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_TPP
#define DTKCOMPOSERTRANSMITTERVARIANT_TPP

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant_p.h"
#include "dtkComposerTransmitterHandler.h"

#include <dtkContainer/dtkContainerVectorWrapper.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkComposerTransmitterVariant::setData(T& data)
{
    dtkComposerTransmitterVariantHandler<T>::setData(data, *this);
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(const T& data)
{
    this->setData(const_cast<T&>(data));
}

template <typename T> void dtkComposerTransmitterVariant::setData(dtkContainerVector<T> *data)
{
    e->data_owner = true;

    if (!d->container)
        d->container = new dtkContainerVectorWrapper<T>(data);
    else
        d->container->setVector(data);

    d->variant.setValue(d->container);
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(const dtkContainerVector<T> *data)
{
    this->setData(const_cast<dtkContainerVector<T>*>(data));
}

template <typename T> T dtkComposerTransmitterVariant::data(void)
{
    return dtkComposerTransmitterVariantHandler<T>::data(*this);
}

template <typename T> T dtkComposerTransmitterVariant::constData(void)
{
    return this->variant().value<T>();

    // if (this->dataTransmission() != dtkComposerTransmitter::Copy) {
    //     return this->variant().value<T*>();

    // } else {
    //     T *data = this->variant().value<T*>();
        
    //     if (!data)
    //         return NULL;
        
    //     if (e->twinned)
    //         return data;

    //     T *m_data;
    //     if (!e->m_variant.isValid())
    //         m_data = NULL;
    //     else
    //         m_data = e->m_variant.value<T*>();

    //     if (!m_data) {
    //         if (dtkComposerTypeInfo<T*>::isAbstractObjectPointer)
    //             m_data = reinterpret_cast<T*>(reinterpret_cast<dtkAbstractObject*>(data)->clone());
    //         else
    //             m_data = new T(*data);
    //         e->m_variant.setValue(m_data);
    //     } else {
    //         *m_data = *data;
    //     }
    //     return m_data;
    // }
    // return NULL;
}

#endif
