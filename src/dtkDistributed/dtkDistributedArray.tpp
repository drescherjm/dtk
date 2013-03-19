/* dtkDistributedArray.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb 18 08:30:17 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedWork.h"
#include "dtkDistributedWorker.h"

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray implementation
// ///////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& count, dtkDistributedWork *work) : m_handler(0), 
														     m_local_handler(*this), 
														     m_global_handler(*this), 
														     m_wid(work->worker()->wid()), 
														     m_count(count), 
														     m_mapper(new dtkDistributedMapper), 
														     m_worker(work->worker()), 
														     m_comm(work->worker()->communicator())
{
    this->initialize();
}

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const QVector<T>& qvector , dtkDistributedWork *work) : m_handler(0), 
															 m_local_handler(*this), 
															 m_global_handler(*this), 
															 m_wid(work->worker()->wid()), 
															 m_count(qvector.count()), 
															 m_mapper(new dtkDistributedMapper), 
															 m_worker(work->worker()), 
															 m_comm(work->worker()->communicator())
{
    this->initialize();
    for (qlonglong i = 0; i <  m_local_handler.buffer_count ; ++i)
        m_local_handler.buffer[i] = qvector.at(localToGlobal(i));

}

template<typename T> dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    m_comm->deallocate(m_wid, buffer_id);

    m_worker->unrecord(this);

    if (m_mapper)
        delete m_mapper;
}

template<typename T> void dtkDistributedArray<T>::initialize(void)
{
    m_worker->record(this);
    this->setMode(dtkDistributed::mode());

    m_mapper->setMapping(m_count, m_comm->size());
    buffer_count = m_mapper->count(m_wid);
    buffer_id = m_worker->containerId(this);

    buffer = static_cast<T*>(m_comm->allocate(buffer_count, sizeof(T), m_wid, buffer_id));

    m_local_handler.buffer_count = buffer_count;
    m_local_handler.buffer = buffer;

    m_global_handler.m_count = m_count;
    m_global_handler.m_wid = m_wid;
    m_global_handler.buffer_id = buffer_id;
    m_global_handler.buffer_count = buffer_count;
    m_global_handler.buffer = buffer;
    m_global_handler.m_mapper = m_mapper;
    m_global_handler.m_comm   = m_comm;
}

template <typename T> void dtkDistributedArray<T>::setMode(const dtkDistributed::Mode& mode)
{
    switch(mode) {
    case dtkDistributed::Local:
        m_handler = &m_local_handler;
        break;
    case dtkDistributed::Global:
        m_handler = &m_global_handler;
        break;
    default:
        m_handler = &m_global_handler;
        break;
    }
}

template<typename T> qlonglong dtkDistributedArray<T>::localToGlobal(const qlonglong& index)
{
    return m_mapper->localToGlobal(index, m_wid);
}

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArray global handler
// ///////////////////////////////////////////////////////////////////

template<typename T> void dtkDistributedArray<T>::global_handler::setAt(const qlonglong& index, const T& value)
{
    qint32 owner = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index);
    m_comm->put(owner, pos, &(const_cast<T&>(value)), buffer_id);
}

template<typename T> T dtkDistributedArray<T>::global_handler::at(const qlonglong& index) const
{
    qint32 owner  = static_cast<qint32>(m_mapper->owner(index));
    qlonglong pos = m_mapper->globalToLocal(index);
    if (m_wid == owner) {
	return buffer[pos];
    } else {
	T temp;
	m_comm->get(owner, pos, &temp, buffer_id);
	return temp;
    }
}

