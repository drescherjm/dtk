/* dtkDistributedArrayHandler.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Tue Feb 26 15:04:40 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> dtkDistributedArrayHandler<T>::dtkDistributedArrayHandler(dtkDistributedArray<T> *array, const qlonglong& count, dtkDistributedWorker *worker) : m_mapper(new dtkDistributedMapper), m_worker(worker), m_wid(worker->wid()), m_count(count), m_comm(worker->communicator()), m_array(array)
{
    this->initialize();
}

template <typename T> dtkDistributedArrayHandler<T>::~dtkDistributedArrayHandler(void)
{
    m_comm->deallocate(m_wid, m_buffer_id);

    m_worker->unrecord(m_array);
    m_array->setMode(dtkDistributed::mode());

    if (m_mapper)
        delete m_mapper;
}

template <typename T> void dtkDistributedArrayHandler<T>::initialize(void) 
{
    m_worker->record(m_array);

    m_mapper->setMapping(m_count, m_comm->size());
    m_buffer_count = m_mapper->count(m_wid);
    m_buffer_id = m_worker->containerId(m_array);

    m_buffer = static_cast<T*>(m_comm->allocate(m_buffer_count, sizeof(T), m_wid, m_buffer_id));
}

template <typename T> void dtkDistributedArrayHandler<T>::setLocalMode(void) 
{
    clearMethod = &dtkDistributedArrayHandler<T>::clearLocal;
    emptyMethod = &dtkDistributedArrayHandler<T>::emptyLocal;
    countMethod = &dtkDistributedArrayHandler<T>::countLocal;

    setMethod = &dtkDistributedArrayHandler<T>::setLocal;
    atMethod  =  &dtkDistributedArrayHandler<T>::atLocal;

    firstMethod = &dtkDistributedArrayHandler<T>::firstLocal;
    lastMethod  =  &dtkDistributedArrayHandler<T>::lastLocal;
}

template <typename T> void dtkDistributedArrayHandler<T>::setGlobalMode(void) 
{
    clearMethod = &dtkDistributedArrayHandler<T>::clearGlobal;
    emptyMethod = &dtkDistributedArrayHandler<T>::emptyGlobal;
    countMethod = &dtkDistributedArrayHandler<T>::countGlobal;

    setMethod = &dtkDistributedArrayHandler<T>::setGlobal;
    atMethod  =  &dtkDistributedArrayHandler<T>::atGlobal;

    firstMethod = &dtkDistributedArrayHandler<T>::firstGlobal;
    lastMethod  =  &dtkDistributedArrayHandler<T>::lastGlobal;
}
    
template <typename T> void dtkDistributedArrayHandler<T>::clear(void)
{ 
    return (this->*clearMethod)(); 
}
    
template <typename T> bool dtkDistributedArrayHandler<T>::empty(void) const 
{ 
    return (this->*emptyMethod)(); 
}
    
template <typename T> qlonglong dtkDistributedArrayHandler<T>::count(void) const 
{ 
    return (this->*countMethod)(); 
}

template<typename T> void dtkDistributedArrayHandler<T>::set(const qlonglong& index, const T& value)
{
    (this->*setMethod)(index, value);
}

template<typename T> void dtkDistributedArrayHandler<T>::setGlobal(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index);
    m_comm->put(owner, pos, &(const_cast<T&>(value)), m_buffer_id);
}

template<typename T> T dtkDistributedArrayHandler<T>::at(const qlonglong& index) const
{
    return (this->*atMethod)(index);
}

template<typename T> T dtkDistributedArrayHandler<T>::atGlobal(const qlonglong& index) const
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));

    qlonglong pos = m_mapper->globalToLocal(index);

    if (m_wid == owner) {
        return m_buffer[pos];

    } else {
        T temp;

        m_comm->get(owner, pos, &temp, m_buffer_id);

        return temp;
    }
}

template<typename T> T dtkDistributedArrayHandler<T>::first(void) const
{
    return (this->*firstMethod)();
}

template<typename T> T dtkDistributedArrayHandler<T>::last(void) const
{
    return (this->*lastMethod)();
}

template<typename T> dtkDistributedIterator<T> dtkDistributedArrayHandler<T>::iterator(void)
{
    return dtkDistributedIterator<T>(new dtkDistributedIteratorArrayPrivate<T>(*this));
}

template<typename T>  qlonglong dtkDistributedArrayHandler<T>::localToGlobal(const qlonglong& index)
{
    return m_mapper->localToGlobal(index, m_wid);
}
