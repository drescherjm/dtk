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

// ///////////////////////////////////////////////////////////////////
// dtkDistributedStaticArray private implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline void dtkDistributedStaticArray<T>::allocate(dtkDistributedBufferManager *& manager, Data *& x, qlonglong size)
{
    manager = m_comm->createBufferManager();
    x = dtkTypedArrayData<T>::fromRawData(manager->allocate<T>(size), size, dtkArrayData::RawData);
}

template <typename T> inline void dtkDistributedStaticArray<T>::deallocate(dtkDistributedBufferManager *manager, Data *x)
{
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
        delete x;
        m_comm->destroyBufferManager(manager);
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkDistributedStaticArray implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkDistributedStaticArray<T>::dtkDistributedStaticArray(const qlonglong& size) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> >(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(m_comm->wid()));
}

template <typename T> inline dtkDistributedStaticArray<T>::dtkDistributedStaticArray(const qlonglong& size, dtkDistributedMapper *mapper) : dtkDistributedContainer(size, mapper),
    data(0), m_cache(new dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> >(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(m_comm->wid()));
}

template <typename T> inline dtkDistributedStaticArray<T>::dtkDistributedStaticArray(const qlonglong& size, const T& init_value) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> >(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(m_comm->wid()));

    this->fill(init_value);
}

template <typename T> inline dtkDistributedStaticArray<T>::dtkDistributedStaticArray(const qlonglong& size, const T *array) : dtkDistributedContainer(size),
    data(0), m_cache(new dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> >(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(m_comm->wid()));

    if (array) {
        for (qlonglong i = 0; i < data->size; ++i) {
            data->begin()[i] = array[m_mapper->localToGlobal(i, m_comm->wid())];
        }
    }
}

template <typename T> inline dtkDistributedStaticArray<T>::dtkDistributedStaticArray(const dtkDistributedStaticArray& o) : dtkDistributedContainer(o.size(), o.mapper()),
    data(0), m_cache(new dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> >(this)), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, data, m_mapper->count(m_comm->wid()));
    
    for (qlonglong i = 0; i < data->size; ++i) {
        data->begin()[i] = o.data->begin()[i];
    }
}

template <typename T> inline dtkDistributedStaticArray<T>::~dtkDistributedStaticArray(void)
{
    this->deallocate(m_buffer_manager, data);
    data = 0;
    m_buffer_manager = 0;

    delete m_cache;
    m_cache = 0;
}

template <typename T> inline void dtkDistributedStaticArray<T>::remap(dtkDistributedMapper *remapper)
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

template<typename T> inline void dtkDistributedStaticArray<T>::rlock(qint32 owner)
{
    m_buffer_manager->rlock(owner);
}

template<typename T> inline void dtkDistributedStaticArray<T>::wlock(qint32 owner)
{
    m_buffer_manager->wlock(owner);
}

template<typename T> inline void dtkDistributedStaticArray<T>::unlock(qint32 owner)
{
    m_buffer_manager->unlock(owner);
}

template<typename T> inline bool dtkDistributedStaticArray<T>::empty(void) const
{
    return !m_size;
}

template<typename T> inline qlonglong dtkDistributedStaticArray<T>::size(void) const
{
    return m_size;
}

template <typename T> inline void dtkDistributedStaticArray<T>::fill(const T& value)
{
    typename Data::iterator it  = data->begin();
    typename Data::iterator end = data->end();
    for(; it != end; ++it) {
        *it = value;
    }
}

template<typename T> inline void dtkDistributedStaticArray<T>::setAt(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, m_comm->wid()));
    qlonglong pos = m_mapper->globalToLocal(index);
    m_buffer_manager->put(owner, pos, &(const_cast<T&>(value)));
}

template<typename T> inline void dtkDistributedStaticArray<T>::setAt(const qlonglong& index, T *array, const qlonglong& size)
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

template<typename T> inline T dtkDistributedStaticArray<T>::at(const qlonglong& index) const
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, m_comm->wid()));

    if (m_comm->wid() == owner) {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        T temp;
        m_buffer_manager->get(owner, pos, &temp);
        return temp;

    } else {
        return m_cache->value(index);
    }
}

template<typename T> inline T dtkDistributedStaticArray<T>::first(void) const
{
    return this->at(0);
}

template<typename T> inline T dtkDistributedStaticArray<T>::last(void) const
{
    return this->at(this->size() - 1);
}

template<typename T> inline T dtkDistributedStaticArray<T>::operator[](qlonglong index) const
{
    return this->at(index);
}

template<typename T> inline void dtkDistributedStaticArray<T>::copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const
{   
    qint32 owner = static_cast<qint32>(m_mapper->owner(from));
    size = qMin(size, m_mapper->lastIndex(owner) - from + 1);
    qlonglong pos = m_mapper->globalToLocal(from);

    m_buffer_manager->get(owner, pos, array, size);
}

template<typename T> inline typename dtkDistributedStaticArray<T>::iterator dtkDistributedStaticArray<T>::begin(iterator)
{ 
    return data->begin(); 
}

template<typename T> inline typename dtkDistributedStaticArray<T>::iterator dtkDistributedStaticArray<T>::end(iterator)
{ 
    return data->end(); 
}

template<typename T> inline typename dtkDistributedStaticArray<T>::const_iterator dtkDistributedStaticArray<T>::begin(const_iterator) const
{ 
    return data->begin();
}

template<typename T> inline typename dtkDistributedStaticArray<T>::const_iterator dtkDistributedStaticArray<T>::end(const_iterator) const
{ 
    return data->end();
}

template<typename T> inline typename dtkDistributedStaticArray<T>::const_iterator dtkDistributedStaticArray<T>::cbegin(const_iterator) const
{
    return data->constBegin();
}

template<typename T> inline typename dtkDistributedStaticArray<T>::const_iterator dtkDistributedStaticArray<T>::cend(const_iterator) const
{ 
    return data->constEnd();
}

template<typename T> inline typename dtkDistributedStaticArray<T>::navigator dtkDistributedStaticArray<T>::toNavigator(void) const
{
    return navigator(*this, 0, size());
}

template<typename T> inline void dtkDistributedStaticArray<T>::stats(void) const
{
    qDebug() << "cache hitrate:" << m_cache->hitrate();
}

// 
// dtkDistributedStaticArray.tpp ends here
