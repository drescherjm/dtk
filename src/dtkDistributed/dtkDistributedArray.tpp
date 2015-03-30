// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedBufferManager.h"

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray private implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline void dtkDistributedArray<T>::allocate(dtkDistributedBufferManager *& manager, Data *& x, qlonglong size)
{
    if (size > 0) {
        manager = m_comm->createBufferManager();
        x = dtkTypedArrayData<T>::fromRawData(manager->allocate<T>(size), size, dtkArrayData::RawData);
    }
}

template <typename T> inline void dtkDistributedArray<T>::deallocate(dtkDistributedBufferManager *manager, Data *x)
{
    if (!x)
        return;

    if (!x->ref.deref()) {
        if (QTypeInfo<T>::isComplex) {
            T *from = x->begin();
            T *to   = x->end();
            while (from != to) {
                from++->~T();
            }
        }
        T *buffer = static_cast<T *>(x->data());
        manager->deallocate(buffer);
        free(x);
        m_comm->destroyBufferManager(manager);
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, dtkDistributedMapper *mapper) : dtkDistributedContainer(size, mapper),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    if (m_mapper->count() == 0)
        m_mapper->setMapping(size, m_comm->size());
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, const T& init_value) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));

    this->fill(init_value);
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, const T *array) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));

    if (array) {
        for (qlonglong i = 0; i < data->size; ++i) {
            data->begin()[i] = array[m_mapper->localToGlobal(i, this->wid())];
        }
    }
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const dtkArray<T>& array) : dtkDistributedContainer(array.size()),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));

    for (qlonglong i = 0; i < data->size; ++i) {
        data->begin()[i] = array[m_mapper->localToGlobal(i, this->wid())];
    }
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const dtkDistributedArray& o) : dtkDistributedContainer(o.size(), o.mapper()),
    data(0), m_cache(new dtkDistributedArrayCache<T>(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(this->wid()));

    if (data) {

        typename Data::iterator oit  = o.data->begin();
        typename Data::iterator oend = o.data->end();
        typename Data::iterator it  = o.data->begin();
        for(; oit != oend; ++oit) {
            *it = *oit;
            it++;
        }
    }
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    m_comm->barrier();
    this->deallocate(m_buffer_manager, data);
    data = 0;
    m_buffer_manager = 0;

    delete m_cache;
    m_cache = 0;
}

template <typename T> inline void dtkDistributedArray<T>::remap(dtkDistributedMapper *remapper)
{
    dtkDistributedBufferManager *new_buffer_manager = 0;
    Data *new_data = 0;

    this->allocate(new_buffer_manager, new_data, remapper->count(this->wid()));
    
    for (qlonglong i = 0; i < new_data->size; ++i) {
        new_data->begin()[i] = this->at(remapper->localToGlobal(i, this->wid()));
    }

    m_comm->barrier();

    this->setMapper(remapper);
    m_cache->clear();
    this->deallocate(m_buffer_manager, data);
    this->m_buffer_manager = new_buffer_manager;
    this->data = new_data;

    m_comm->barrier();
}

template<typename T> inline void dtkDistributedArray<T>::rlock(qint32 owner)
{
    m_buffer_manager->rlock(owner);
}

template<typename T> inline void dtkDistributedArray<T>::wlock(qint32 owner)
{
    m_buffer_manager->wlock(owner);
}

template<typename T> inline void dtkDistributedArray<T>::unlock(qint32 owner)
{
    m_buffer_manager->unlock(owner);
}

template<typename T> inline void dtkDistributedArray<T>::rlock(void)
{
    m_buffer_manager->rlock();
}

template<typename T> inline void dtkDistributedArray<T>::wlock(void)
{
    m_buffer_manager->wlock();
}

template<typename T> inline void dtkDistributedArray<T>::unlock(void)
{
    m_buffer_manager->unlock();
}

template<typename T> inline bool dtkDistributedArray<T>::empty(void) const
{
    return !m_size;
}

template<typename T> inline void dtkDistributedArray<T>::clearCache(void) const
{
    m_cache->clear();
}

template<typename T> inline qlonglong dtkDistributedArray<T>::size(void) const
{
    return m_size;
}

template <typename T> inline void dtkDistributedArray<T>::fill(const T& value)
{
    typename Data::iterator it  = data->begin();
    typename Data::iterator end = data->end();
    for(; it != end; ++it) {
        *it = value;
    }
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, this->wid()));
    qlonglong pos = m_mapper->globalToLocal(index);
    m_buffer_manager->put(owner, pos, &(const_cast<T&>(value)));
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, T *array, const qlonglong& size)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (size <= owner_capacity) {
        m_buffer_manager->put(owner, pos, array, size);
    
    } else {
        m_buffer_manager->put(owner, pos, array, owner_capacity);
        this->setAt(index + owner_capacity, array + owner_capacity, size - owner_capacity);
    }
}

template<typename T> inline T dtkDistributedArray<T>::at(const qlonglong& index) const
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, this->wid()));

    if (this->wid() == owner) {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        T temp;
        m_buffer_manager->get(owner, pos, &temp);
        return temp;

    } else {
        return m_cache->value(index);
    }
}

template<typename T> inline T dtkDistributedArray<T>::first(void) const
{
    return this->at(0);
}

template<typename T> inline T dtkDistributedArray<T>::last(void) const
{
    return this->at(this->size() - 1);
}

template<typename T> inline T dtkDistributedArray<T>::operator[](qlonglong index) const
{
    return this->at(index);
}

template<typename T> inline void dtkDistributedArray<T>::copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const
{   
    qint32 owner = static_cast<qint32>(m_mapper->owner(from));
    size = qMin(size, m_mapper->lastIndex(owner) - from + 1);
    qlonglong pos = m_mapper->globalToLocal(from);

    m_buffer_manager->get(owner, pos, array, size);
}

template<typename T> inline typename dtkDistributedArray<T>::iterator dtkDistributedArray<T>::begin(iterator)
{ 
    return data->begin(); 
}

template<typename T> inline typename dtkDistributedArray<T>::iterator dtkDistributedArray<T>::end(iterator)
{ 
    return data->end(); 
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::begin(const_iterator) const
{ 
    return data->begin();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::end(const_iterator) const
{ 
    return data->end();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::cbegin(const_iterator) const
{
    return data->constBegin();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::cend(const_iterator) const
{ 
    return data->constEnd();
}

template<typename T> inline typename dtkDistributedArray<T>::navigator dtkDistributedArray<T>::toNavigator(void) const
{
    return navigator(*this, 0, size());
}

template<typename T> inline void dtkDistributedArray<T>::stats(void) const
{
    qDebug() << "cache hitrate:" << m_cache->hitrate();
}

// 
// dtkDistributedArray.tpp ends here
