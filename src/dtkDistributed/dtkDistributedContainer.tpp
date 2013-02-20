/* dtkDistributedContainer.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:12:49 2013 (+0100)
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkDistributedMapper.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(const qlonglong& size, dtkDistributedWorker *worker) : m_buffer(0), m_temp(0), m_loc_it(0), m_glob_it(0), m_global_size(size), m_mapper(new dtkDistributedMapper), m_comm(worker->communicator()), m_worker(worker)
{
    m_comm->initialize();

    qDebug() << "start container with size " <<  size << "and comm size" << m_comm->size()  << "rank" << m_worker->wid();
    m_buffer_id = m_worker->containerId();
    m_mapper->setMapping(m_global_size, m_comm->size());

    this->allocate();
};

template<typename T> dtkDistributedContainer<T>::~dtkDistributedContainer(void)
{
    m_comm->deallocate( m_worker->wid(), m_buffer_id);

    if (m_loc_it)
        delete m_loc_it;

    if (m_glob_it)
        delete m_glob_it;

    delete m_mapper;
};

template<typename T> void dtkDistributedContainer<T>::allocate(void)
{
    m_buffer_size = m_mapper->count(m_worker->wid());
    m_buffer = static_cast<T*>(m_comm->allocate(m_mapper->count(m_worker->wid()), sizeof(T), m_worker->wid(), m_buffer_id));
};

template<typename T> void dtkDistributedContainer<T>::deallocate(void)
{
    m_comm->deallocate( m_worker->wid(), m_buffer_id);
};

template <typename T> qlonglong dtkDistributedContainer<T>::size(void) const
{
    return m_global_size;
};

template <typename T> void dtkDistributedContainer<T>::set(const qlonglong& global_id, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(global_id));
    qlonglong pos = m_mapper->globalToLocal(global_id);
    m_comm->put(owner, pos, &(const_cast<T&>(value)), m_buffer_id);
};

template <typename T> void dtkDistributedContainer<T>::setLocal(const qlonglong& local_id, const T& value)
{
    m_buffer[local_id] = value;
};

template <typename T> T dtkDistributedContainer<T>::at(const qlonglong& global_id)
{
    qint32 me = m_worker->wid();
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

    m_loc_it->toFront();

    return *m_loc_it;
};

template <typename T> dtkDistributedGlobalIterator<T>& dtkDistributedContainer<T>::globalIterator(void)
{
    if (!m_glob_it)
        m_glob_it = new dtkDistributedGlobalIterator<T>(*this);

    m_glob_it->toFront();

    return *m_glob_it;
};

template <typename T> dtkDistributedIterator<T>& dtkDistributedContainer<T>::iterator(void)
{
    if (!m_glob_it)
        m_it = new dtkDistributedIterator<T>(*this);

    m_it->toFront();

    return *m_it;
};
