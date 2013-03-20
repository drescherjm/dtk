/* dtkComposerTransmitterHandler.tpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 13:16:32 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 13:17:10 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERHANDLER_TPP
#define DTKCOMPOSERTRANSMITTERHANDLER_TPP

#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerVariant.h"

// #include <dtkContainer>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> T *dtkComposerTransmitterHandler<T, U>::copyData(T *data, T*& copy, bool enable_copy)
{
    if (!data || !enable_copy)
        return data;

    if (!copy)
        copy = new T(*data);
    else
        *copy = *data;

    return copy;
}

template <typename T, bool U> T *dtkComposerTransmitterHandler<T, U>::copyData(T *data, T*& copy, bool enable_copy, dtkComposerVariant& variant)
{
    if (!data || !enable_copy)
        return data;

    if (!copy) {
        copy = new T(*data);
        variant.setValue(copy);
    } else {
        *copy = *data;
    }

    return copy;
}

template <typename T> T *dtkComposerTransmitterHandler<T, true>::copyData(T *data, T*& copy, bool enable_copy)
{
    if (!data || !enable_copy)
        return data;

    if (!copy)
        copy = data->clone();
    else
        *copy = *data;

    return copy;
}

template <typename T> T *dtkComposerTransmitterHandler<T, true>::copyData(T *data, T*& copy, bool enable_copy, dtkComposerVariant& variant)
{
    if (!data || !enable_copy)
        return data;

    if (!copy) {
        copy = data->clone();
        variant.setValue(copy);
    } else {
        *copy = *data;
    }

    return copy;
}

template <typename T> void dtkComposerTransmitterVariantHandler<T>::setData(T& data, dtkComposerTransmitterVariant& t_variant)
{
    t_variant.d->variant.setValue(data);
    if (t_variant.d->container) {
        delete t_variant.d->container;
        t_variant.d->container = NULL;
    }
}

template <typename T> T dtkComposerTransmitterVariantHandler<T>::data(dtkComposerTransmitterVariant& t_variant)
{
    return t_variant.variant().value<T>();
}

template <typename T> void dtkComposerTransmitterVariantHandler<T*>::setData(T *data, dtkComposerTransmitterVariant& t_variant)
{
    t_variant.d->variant.setValue(data);
    if (t_variant.d->container) {
        delete t_variant.d->container;
        t_variant.d->container = NULL;
    }
}

template <typename T> T *dtkComposerTransmitterVariantHandler<T*>::data(dtkComposerTransmitterVariant& t_variant)
{
    T *data = t_variant.variant().value<T*>();

    if (t_variant.e->twinned)
        return data;

    if (!data)
        return NULL;

    T *m_data;
    if (!t_variant.e->m_variant.isValid())
        m_data = NULL;
    else
        m_data = t_variant.e->m_variant.value<T*>();

    return dtkComposerTransmitterHandler<T, dtkComposerTypeInfo<T*>::isObjectPointer>::copyData(data, m_data, t_variant.enableCopy(), t_variant.e->m_variant);
}

#endif
