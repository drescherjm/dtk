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

//#prama once

#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"

class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker) : m_mapper(new dtkDistributedMapper), m_worker(worker)
{
    m_mapper->setMapping(count, m_worker->communicator()->size());

    m_handler.initialize(m_worker->communicator(), m_worker->wid(), count, m_mapper->count(m_worker->wid()), m_worker->containerId());
}

template<typename T> dtkDistributedArray<T>::~dtkDistributedArray(void)
{

}

template<typename T> void dtkDistributedArray<T>::clear(void)
{
    return m_handler.clear();
}

template<typename T> bool dtkDistributedArray<T>::empty(void) const
{
    return m_handler.empty();
}

template<typename T> qlonglong dtkDistributedArray<T>::count(void) const
{
    return m_handler.count();
}

