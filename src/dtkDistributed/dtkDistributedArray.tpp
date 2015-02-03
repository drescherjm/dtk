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

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedContainer.h"
#include "dtkDistributedMapper.h"

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray private implementation
// ///////////////////////////////////////////////////////////////////

template<typename T> inline void dtkDistributedArray<T>::allocate(Data *& x, qint64& x_id, qlonglong size)
{
    T *array = static_cast<T *>(m_comm->allocate(size, sizeof(T), this->wid(), x_id));
    x = dtkTypedArrayData<T>::fromRawData(array, size, dtkArrayData::RawData);
}

template<typename T> inline void dtkDistributedArray<T>::freeData(Data *x, qint64 x_id)
{
    if (!x->ref.deref()) {
        if (QTypeInfo<T>::isComplex) {
            T *from = x->begin();
            T *to   = x->end();
            while (from != to) {
                from++->~T();
            }
        }
        m_comm->deallocate(this->wid(), x_id);
        delete x;
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray implementation
// ///////////////////////////////////////////////////////////////////

template<typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size) : 
    dtkDistributedContainer(size), data(0), cache(new dtkDistributedArrayCache<T>(this))
{
    this->allocate(this->data, this->data_id, m_mapper->count(this->wid()));
}

template<typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size,  dtkDistributedMapper *mapper) : 
    dtkDistributedContainer(size, mapper), data(0), cache(new dtkDistributedArrayCache<T>(this))
{
    this->allocate(this->data, this->data_id, m_mapper->count(this->wid()));
}

template<typename T> inline dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& size, const T *array) : 
    dtkDistributedContainer(size), data(0), cache(new dtkDistributedArrayCache<T>(this))
{
    qlonglong count = m_mapper->count(this->wid());
    this->allocate(this->data, this->data_id, count);    
    for (qlonglong i = 0; i < count; ++i) {
        data->begin()[i] = array[m_mapper->localToGlobal(i, this->wid())];
    }
}

template<typename T> inline dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    this->freeData(data, data_id);

    delete cache;
}

template<typename T> inline void dtkDistributedArray<T>::remap(dtkDistributedMapper *remapper)
{
    qlonglong size = remapper->count(this->wid());
    Data *x;
    qint64 x_id;
    this->allocate(x, x_id, size);
    
    for (qlonglong i = 0; i < size; ++i) {
        x->begin()[i] = this->at(remapper->localToGlobal(i, this->wid()));
    }

    delete m_mapper;
    m_mapper = remapper;

    m_comm->barrier();
    cache->clear();
    this->freeData(this->data, this->data_id);

    this->data = x;
    this->data_id = x_id;
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, this->wid()));
    qlonglong pos = m_mapper->globalToLocal(index);
    m_comm->put(owner, pos, &(const_cast<T&>(value)), this->data_id);
}

template<typename T> inline void dtkDistributedArray<T>::setAt(const qlonglong& index, T *array, const qlonglong& size)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index);

    qlonglong owner_capacity = m_mapper->lastIndex(owner) - index + 1;

    if (size <= owner_capacity) {
        m_comm->put(owner, pos, array, this->data_id, size);
    
    } else {
        m_comm->put(owner, pos, array, this->data_id, owner_capacity);
        this->setAt(index + owner_capacity, array + owner_capacity, size - owner_capacity);
    }
}

template<typename T> inline T dtkDistributedArray<T>::at(const qlonglong& index) const
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index, this->wid()));

    if (this->wid() == owner) {
        qlonglong pos = m_mapper->globalToLocal(index, owner);
        T temp;
        m_comm->get(owner, pos, &temp, this->data_id);
        return temp;

    } else {
        return cache->value(index);
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

template<typename T> inline void dtkDistributedArray<T>::copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const
{   
    qint32 owner = static_cast<qint32>(m_mapper->owner(from));
    size = qMin(size, m_mapper->lastIndex(owner) - from + 1);
    qlonglong pos = m_mapper->globalToLocal(from);

    m_comm->get(owner, pos, array, this->data_id, size);
}

template<typename T> inline void dtkDistributedArray<T>::rlock(qint32 owner)
{
    m_comm->rlock(owner, this->data_id);
}

template<typename T> inline void dtkDistributedArray<T>::wlock(qint32 owner)
{
    m_comm->wlock(owner, this->data_id);
}

template<typename T> inline void dtkDistributedArray<T>::unlock(qint32 owner)
{
    m_comm->unlock(owner, this->data_id);
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
    return data->cbegin();
}

template<typename T> inline typename dtkDistributedArray<T>::const_iterator dtkDistributedArray<T>::cend(const_iterator) const
{ 
    return data->cend();
}

template<typename T> inline void dtkDistributedArray<T>::stats(void) const
{
    qDebug() << "cache hitrate:" << cache->hitrate();
}

// 
// dtkDistributedArray.tpp ends here
