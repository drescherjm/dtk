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

#include <dtkContainer/dtkContainerVectorWrapper.h>

// /////////////////////////////////////////////////////////////////
// Forward declaration of specialized method
// /////////////////////////////////////////////////////////////////

template <> DTKCOMPOSER_EXPORT bool      *dtkComposerTransmitterVariant::data(void);
template <> DTKCOMPOSER_EXPORT qlonglong *dtkComposerTransmitterVariant::data(void);
template <> DTKCOMPOSER_EXPORT qreal     *dtkComposerTransmitterVariant::data(void);
template <> DTKCOMPOSER_EXPORT QString   *dtkComposerTransmitterVariant::data(void);

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////


template <typename T> void dtkComposerTransmitterVariant::setData(T *data)
{
    d->data_type = qMetaTypeId<T>(reinterpret_cast<T*>(0));

    d->variant.setValue(data);
    if (d->container) {
        delete d->container;
        d->container = NULL;
    }

    if (dtkTypeInfo<T*>::dtkAbstractObjectPointer) {
        d->object = reinterpret_cast<dtkAbstractObject*>(data);
        d->matrix = NULL;

    } else if (dtkTypeInfo<T*>::dtkMatrixRealPointer) {
        d->object = NULL;
        d->matrix = reinterpret_cast<dtkMatrix<double>*>(data);

    } else {
        d->object = NULL;
        d->matrix = NULL;
    }
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(const T *data)
{
    this->setData(const_cast<T*>(data));
}

template <typename T> void dtkComposerTransmitterVariant::setData(dtkContainerVector<T> *data)
{
    e->data_owner = true;
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper*>(0));

    if (!d->container)
        d->container = new dtkContainerVectorWrapper<T>(data);
    else
        d->container->setVector(data);

    d->variant.setValue(d->container);
    
    d->object = d->container;
}

template <typename T> inline void dtkComposerTransmitterVariant::setData(const dtkContainerVector<T> *data)
{
    this->setData(const_cast<dtkContainerVector<T>*>(data));
}

template <typename T> T *dtkComposerTransmitterVariant::data(void)
{
    T *data = NULL;

    if (dtkTypeInfo<T*>::dtkAbstractObjectPointer) {
        dtkAbstractObject * o = this->object();
        if  (o && dtkTypeInfo<T*>::dtkAbstractObjectPointer) {
            data=reinterpret_cast<T*>(o);
        } else {
            data = this->variant().value<T*>();
        }

    } else
        data = this->variant().value<T*>();

    if (e->twinned)
        return data;

    if (!data)
        return NULL;

    T *m_data;
    if (!e->m_variant.isValid())
        m_data = NULL;
    else
        m_data = e->m_variant.value<T*>();

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
        if (this->enableCopy()) {
            if (!m_data) {
                if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
                    m_data = reinterpret_cast<T*>(reinterpret_cast<dtkAbstractObject*>(data)->clone());
                else
                    m_data = new T(*data);
                e->m_variant.setValue(m_data);
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
            if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
                m_data = reinterpret_cast<T*>(reinterpret_cast<dtkAbstractObject*>(data)->clone());
            else
                m_data = new T(*data);
            e->m_variant.setValue(m_data);
        } else {
            *m_data = *data;
        }
        return m_data;
        break;
    case dtkComposerTransmitter::Reference:
        return data;
        break;
    default:
        break;
    };

    return NULL;
}

template <typename T> const T *dtkComposerTransmitterVariant::constData(void)
{
    if (this->dataTransmission() != dtkComposerTransmitter::Copy) {
        if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
            return reinterpret_cast<T*>(this->object());
        else
            return this->variant().value<T*>();

    } else {
        T *data = NULL;

        if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
            data = reinterpret_cast<T*>(this->object());
        else
            data = this->variant().value<T*>();
        
        if (e->twinned)
            return data;

        T *m_data;
        if (!e->m_variant.isValid())
            m_data = NULL;
        else
            m_data = e->m_variant.value<T*>();

        if (!m_data) {
            if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
                m_data = reinterpret_cast<T*>(reinterpret_cast<dtkAbstractObject*>(data)->clone());
            else
                m_data = new T(*data);
            e->m_variant.setValue(m_data);
        } else {
            *m_data = *data;
        }
        return m_data;
    }
    return NULL;
}

#endif
