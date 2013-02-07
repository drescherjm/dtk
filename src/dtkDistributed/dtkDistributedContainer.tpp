/* dtkDistributedContainer.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:12:49 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb  7 17:05:30 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 139
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkDistributedMapper.h"
#include "dtkDistributedCommunicator.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedLocalIterator<T>::dtkDistributedLocalIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_array.constBegin()), m_index(0)
{

};
 
template<typename T> dtkDistributedLocalIterator<T>::~dtkDistributedLocalIterator(void)
{

};

template <typename T> void dtkDistributedLocalIterator<T>::toBack(void)
{
    i = c.m_array.constEnd();
    m_index = c.m_array.size()-1;
};

template <typename T> void dtkDistributedLocalIterator<T>::toFront(void)
{
    i = c.m_array.constBegin();
    m_index = 0;
};

template <typename T> bool dtkDistributedLocalIterator<T>::hasNext(void)
{
    return (i != c.m_array.constEnd());
};

template <typename T> bool dtkDistributedLocalIterator<T>::hasPrevious(void)
{
    return (i != c.m_array.constBegin());
};

template <typename T> const T& dtkDistributedLocalIterator<T>::next(void)
{
    ++m_index;
    return (*i++);
};

template <typename T> const T& dtkDistributedLocalIterator<T>::previous(void)
{
    --m_index;
    return *(--i);
};

template <typename T> const T& dtkDistributedLocalIterator<T>::peekNext(void)
{
    return *i;
};

template <typename T> const T& dtkDistributedLocalIterator<T>::peekPrevious(void)
{
     const_iterator p = i;
     return (*--p);
};


template <typename T> qlonglong dtkDistributedLocalIterator<T>::localIndex(void) const
{
    return m_index;
};

template <typename T> qlonglong dtkDistributedLocalIterator<T>::globalIndex(void) const
{
    return m_index;
};


// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(void) : m_buffer(0), m_iterator(0), m_mapper(new dtkDistributedMapper), m_comm(0), m_temp(0)
{

};

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(const qlonglong& size, dtkDistributedCommunicator *communicator) : m_buffer(0), m_temp(0), m_iterator(0), m_mapper(new dtkDistributedMapper), m_comm(communicator)
{
    this->resize(size);

    m_comm->initialize();

    m_mapper->setMapping(size, m_comm->size());

    this->allocate();
};

template<typename T> dtkDistributedContainer<T>::~dtkDistributedContainer(void)
{
    delete m_iterator;
    delete m_mapper;
};

template<typename T> void dtkDistributedContainer<T>::allocate(void)
{
    qDebug() << __func__;
    m_buffer = new T[m_mapper->count(m_comm->rank())];
    // m_buffer_id = m_comm->allocate(m_mapper->count(m_comm->rank()), sizeof(T), m_buffer);
};

template<typename T> void dtkDistributedContainer<T>::resize(const qlonglong& size)
{
    m_mapper->setMapping(size, 1);
    m_buffer = new T[size];
    m_array.resize(size);
};

template <typename T> qlonglong dtkDistributedContainer<T>::size(void) const
{
    return m_array.size();
};

template <typename T> void dtkDistributedContainer<T>::set(const qlonglong& global_id, const T& value)
{
    m_buffer[m_mapper->globalToLocal(global_id)] = value;
    //m_array.replace(global_id, value);
};

template <typename T> void dtkDistributedContainer<T>::setLocal(const qlonglong& local_id, const T& value)
{
    m_buffer[local_id] = value;
};

template <typename T> T dtkDistributedContainer<T>::at(const qlonglong& global_id)
{
    qint32 me = m_comm->rank();
    qint32 owner = static_cast<qint32>(m_mapper->owner(global_id));

    qlonglong pos = m_mapper->globalToLocal(global_id);

    if (me == owner) {
        return m_buffer[pos];
        
    } else {
        if (!m_temp)
            m_temp = new T[1];

        m_comm->get(owner, pos, m_temp, m_buffer_id);

        return m_temp[0];
    }
}
;
template <typename T> const T& dtkDistributedContainer<T>::localAt(const qlonglong& local_id)
{
    return m_buffer[local_id];
};

template <typename T> dtkDistributedLocalIterator<T>& dtkDistributedContainer<T>::localIterator(void)
{
    if (!m_iterator)
        m_iterator = new dtkDistributedLocalIterator<T>(*this);

    return *m_iterator;
};
