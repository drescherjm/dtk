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
        if (!m_cache)
            m_cache = new dtkDistributedArrayCache<T>(this);
        x = dtkTypedArrayData<T>::fromRawData(manager->allocate<T>(size), size, dtkArrayData::RawData);
    } else {
        qWarning() << "allocation with size == 0 !" << m_comm->wid();
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

template <typename T> inline void dtkDistributedArray<T>::copyConstruct(const T *srcFrom, const T *srcTo, T *dstFrom)
{
    if (QTypeInfo<T>::isComplex) {
        while (srcFrom != srcTo)
            new (dstFrom++) T(*srcFrom++);
    } else {
        ::memcpy(static_cast<void *>(dstFrom), static_cast<const void *>(srcFrom), (srcTo - srcFrom) * sizeof(T));
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size) : dtkDistributedContainer(size),
                                                                                                  d(0), m_cache(0), m_buffer_manager(0)
{
    firstIndex = m_mapper->firstIndex(this->wid());
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, dtkDistributedMapper *mapper) : dtkDistributedContainer(size, mapper),
    d(0), m_cache(0), m_buffer_manager(0)
{
    if (m_mapper->count() == 0)
        m_mapper->setMapping(size, m_comm->size());

    firstIndex = m_mapper->firstIndex(this->wid());
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, const T& init_value) : dtkDistributedContainer(size),
    d(0), m_cache(0), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));

    firstIndex = m_mapper->firstIndex(this->wid());
    this->fill(init_value);
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, const T *array) : dtkDistributedContainer(size),
    d(0), m_cache(0), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));

    if (array) {
        for (qlonglong i = 0; i < d->size; ++i) {
            d->begin()[i] = array[m_mapper->localToGlobal(i, this->wid())];
        }
    }
    firstIndex = m_mapper->firstIndex(this->wid());
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const dtkArray<T>& array) : dtkDistributedContainer(array.size()),
    d(0), m_cache(0), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));

    for (qlonglong i = 0; i < d->size; ++i) {
        d->begin()[i] = array[m_mapper->localToGlobal(i, this->wid())];
    }
    firstIndex = m_mapper->firstIndex(this->wid());
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const dtkDistributedArray& o) : dtkDistributedContainer(o.size(), o.mapper()),
    d(0), m_cache(0), m_buffer_manager(0)
{
    this->allocate(m_buffer_manager, d, m_mapper->count(this->wid()));

    if (d) {

        typename Data::iterator oit  = o.d->begin();
        typename Data::iterator oend = o.d->end();
        typename Data::iterator it   = d->begin();
        for(; oit != oend; ++oit) {
            *it = *oit;
            ++it;
        }
    }
    firstIndex = m_mapper->firstIndex(this->wid());
    m_comm->barrier();
}

template <typename T> inline dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    this->clear();
}

template <typename T> inline dtkDistributedArray<T>& dtkDistributedArray<T>::operator = (const dtkDistributedArray<T>& other)
{
    if (m_size == other.m_size) {
        copyConstruct(other.d->begin(), other.d->end(), d->begin());
        m_cache->clear();
    } else {
        qCritical() << "can't copy: not the same size!"<<  m_size << other.m_size;
        this->clear();
    }
    return *this;
}

template <typename T> inline void dtkDistributedArray<T>::clear(void)
{
    m_comm->barrier();
    this->deallocate(m_buffer_manager, d);
    d = 0;
    m_buffer_manager = 0;

    delete m_cache;
    m_cache = 0;
}

template <typename T> inline void dtkDistributedArray<T>::remap(dtkDistributedMapper *remapper)
{
    dtkDistributedBufferManager *new_buffer_manager = 0;
    Data *new_d = 0;
    this->allocate(new_buffer_manager, new_d, remapper->count(this->wid()));

    if (!new_d) {
        return;
    }

    for (qlonglong i = 0; i < new_d->size; ++i) {
        new_d->begin()[i] = this->at(remapper->localToGlobal(i, this->wid()));
    }

    m_comm->barrier();

    this->setMapper(remapper);
    m_cache->clear();
    this->deallocate(m_buffer_manager, d);
    this->m_buffer_manager = new_buffer_manager;
    this->d = new_d;

    firstIndex = m_mapper->firstIndex(this->wid());
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
    locked = true;
}

template<typename T> inline void dtkDistributedArray<T>::wlock(void)
{
    m_buffer_manager->wlock();
    locked = true;
}

template<typename T> inline void dtkDistributedArray<T>::unlock(void)
{
    m_buffer_manager->unlock();
    locked = false;
}

template<typename T> inline bool dtkDistributedArray<T>::empty(void) const
{
    return !m_size;
}

template<typename T> inline void dtkDistributedArray<T>::clearCache(void) const
{
    m_cache->clear();
}

template<typename T> inline void dtkDistributedArray<T>::enableCache(void) const
{
    m_cache->enable();
}

template<typename T> inline void dtkDistributedArray<T>::disableCache(void) const
{
    m_cache->disable();
}

template<typename T> inline qlonglong dtkDistributedArray<T>::size(void) const
{
    return m_size;
}

template <typename T> inline void dtkDistributedArray<T>::fill(const T& value)
{
    typename Data::iterator it  = d->begin();
    typename Data::iterator end = d->end();
    for(; it != end; ++it) {
        *it = value;
    }
    m_cache->clear();
    m_comm->barrier();
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    if (this->wid() == owner) {
        qlonglong pos = index-firstIndex;
        if (locked){
            d->data()[pos] = value;
        } else {
            m_buffer_manager->put(owner, pos, &(const_cast<T&>(value)));
        }
    } else {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        m_buffer_manager->put(owner, pos, &(const_cast<T&>(value)));
    }
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, T *array, const qlonglong& size)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

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
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));

    if (this->wid() == owner) {
        qlonglong pos = index-firstIndex;
        if (locked){
            return d->data()[pos];
        } else {
            m_buffer_manager->get(owner, pos, &val);
            return val;
        }

    } else if (m_buffer_manager->shouldCache(owner)) {
        return m_cache->value(index, owner);
    } else {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        m_buffer_manager->get(owner, pos, &val);
        return val;
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

template<typename T> inline T dtkDistributedArray<T>::operator[](const qlonglong& index) const
{
    return this->at(index);
}

template<typename T> inline void dtkDistributedArray<T>::addAssign(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    if (this->wid() == owner) {
        qlonglong pos = index - firstIndex;
        if (locked){
            d->data()[pos] += value;
        } else {
            m_buffer_manager->addAssign(owner, pos, &(const_cast<T&>(value)));
        }
    } else {
        qlonglong pos = m_mapper->globalToLocal(index,owner);
        m_buffer_manager->addAssign(owner, pos, &(const_cast<T&>(value)));
    }
}

template<typename T> inline void dtkDistributedArray<T>::subAssign(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    if (this->wid() == owner) {
        qlonglong pos = index - firstIndex;
        if (locked){
            d->data()[pos] -= value;
        } else {
            m_buffer_manager->subAssign(owner, pos, &(const_cast<T&>(value)));
        }
    } else {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        m_buffer_manager->subAssign(owner, pos, &(const_cast<T&>(value)));
    }
}

template<typename T> inline void dtkDistributedArray<T>::mulAssign(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    if (this->wid() == owner) {
        qlonglong pos = index - firstIndex;
        if (locked){
            d->data()[pos] *= value;
        } else {
            m_buffer_manager->mulAssign(owner, pos, &(const_cast<T&>(value)));
        }
    } else {
        qlonglong pos = m_mapper->globalToLocal(index,owner);
        m_buffer_manager->mulAssign(owner, pos, &(const_cast<T&>(value)));
    }
}

template<typename T> inline void dtkDistributedArray<T>::divAssign(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    if (this->wid() == owner) {
        qlonglong pos = index - firstIndex;
        if (locked){
            d->data()[pos] /= value;
        } else {
            m_buffer_manager->divAssign(owner, pos, &(const_cast<T&>(value)));
        }
    } else {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        m_buffer_manager->divAssign(owner, pos, &(const_cast<T&>(value)));
    }
}


template<typename T> inline bool dtkDistributedArray<T>::compareAndSwap(const qlonglong& index, T& array, T& compare)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    return m_buffer_manager->compareAndSwap(owner, pos, &array, &compare);
}

template<typename T> inline void dtkDistributedArray<T>::addAssign(const qlonglong& index, T* array, const qlonglong& count)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (count <= owner_capacity) {
        m_buffer_manager->addAssign(owner, pos, array, count);

    } else {
        m_buffer_manager->addAssign(owner, pos, array, owner_capacity);
        this->addAssign(index + owner_capacity, array + owner_capacity, count - owner_capacity);
    }
}

template<typename T> inline void dtkDistributedArray<T>::subAssign(const qlonglong& index, T* array, const qlonglong& count)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (count <= owner_capacity) {
        m_buffer_manager->subAssign(owner, pos, array, count);

    } else {
        m_buffer_manager->subAssign(owner, pos, array, owner_capacity);
        this->subAssign(index + owner_capacity, array + owner_capacity, count - owner_capacity);
    }
}

template<typename T> inline void dtkDistributedArray<T>::mulAssign(const qlonglong& index, T* array, const qlonglong& count)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (count <= owner_capacity) {
        m_buffer_manager->mulAssign(owner, pos, array, count);

    } else {
        m_buffer_manager->mulAssign(owner, pos, array, owner_capacity);
        this->mulAssign(index + owner_capacity, array + owner_capacity, count - owner_capacity);
    }
}

template<typename T> inline void dtkDistributedArray<T>::divAssign(const qlonglong& index, T* array, const qlonglong& count)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (count <= owner_capacity) {
        m_buffer_manager->divAssign(owner, pos, array, count);

    } else {
        m_buffer_manager->divAssign(owner, pos, array, owner_capacity);
        this->divAssign(index + owner_capacity, array + owner_capacity, count - owner_capacity);
    }
}

template<typename T> inline void dtkDistributedArray<T>::copyIntoArray(const qlonglong& index, const qint32& owner, T *array, qlonglong& size) const
{
    size = qMin(size, m_mapper->lastIndex(owner) - index + 1);
    qlonglong pos = m_mapper->globalToLocal(index, owner);

    m_buffer_manager->get(owner, pos, array, size);
}

template<typename T> inline typename dtkDistributedArray<T>::iterator dtkDistributedArray<T>::begin(iterator)
{ 
    return d->begin(); 
}

template<typename T> inline typename dtkDistributedArray<T>::iterator dtkDistributedArray<T>::end(iterator)
{ 
    return d->end(); 
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::begin(const_iterator) const
{ 
    return d->begin();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::end(const_iterator) const
{ 
    return d->end();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::cbegin(const_iterator) const
{
    return d->constBegin();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::cend(const_iterator) const
{ 
    return d->constEnd();
}

template<typename T> inline const T *dtkDistributedArray<T>::data(void) const
{
    return d->data();
}

template<typename T> inline T *dtkDistributedArray<T>::data(void)
{
    return d->data();
}

template<typename T> inline const T *dtkDistributedArray<T>::constData(void) const
{
    return d->data();
}

template<typename T> inline typename dtkDistributedArray<T>::navigator dtkDistributedArray<T>::toNavigator(void) const
{
    return navigator(*this, 0, size());
}

template<typename T> inline void dtkDistributedArray<T>::stats(void) const
{
    qDebug() << m_comm->rank() << "cache hitrate:" << m_cache->hitrate();
}

// 
// dtkDistributedArray.tpp ends here
