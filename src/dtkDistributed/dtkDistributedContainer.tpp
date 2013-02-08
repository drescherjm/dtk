/* dtkDistributedContainer.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:12:49 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Fri Feb  8 15:56:49 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 174
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkDistributedMapper.h"
#include "dtkDistributedCommunicator.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(const qlonglong& size, dtkDistributedCommunicator *communicator) : m_buffer(0), m_temp(0), m_loc_it(0), m_glob_it(0), m_global_size(size), m_mapper(new dtkDistributedMapper), m_comm(communicator)
{
    m_comm->initialize();

    m_mapper->setMapping(m_global_size, m_comm->size());

    this->allocate();
};

template<typename T> dtkDistributedContainer<T>::~dtkDistributedContainer(void)
{
    if (m_loc_it)
        delete m_loc_it;

    if (m_glob_it)
        delete m_glob_it;

    delete m_mapper;
};

template<typename T> void dtkDistributedContainer<T>::allocate(void)
{
    m_buffer_size = m_mapper->count(m_comm->rank());
    m_buffer = new T[m_buffer_size];
    // m_buffer_id = m_comm->allocate(m_mapper->count(m_comm->rank()), sizeof(T), m_buffer);
};

template <typename T> qlonglong dtkDistributedContainer<T>::size(void) const
{
    return m_global_size;
};

template <typename T> void dtkDistributedContainer<T>::set(const qlonglong& global_id, const T& value)
{
    m_buffer[m_mapper->globalToLocal(global_id)] = value;
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
    if (!m_loc_it)
        m_loc_it = new dtkDistributedLocalIterator<T>(*this);

    return *m_loc_it;
};

template <typename T> dtkDistributedGlobalIterator<T>& dtkDistributedContainer<T>::globalIterator(void)
{
    if (!m_glob_it)
        m_glob_it = new dtkDistributedGlobalIterator<T>(*this);

    return *m_glob_it;
};
