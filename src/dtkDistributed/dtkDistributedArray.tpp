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

#include "dtkDistributed.h"

class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker) : m_handler(new dtkDistributedArrayHandler<T>(this, count, worker))
{

}

template<typename T> dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    if (m_handler)
        delete m_handler;
}

template <typename T> void dtkDistributedArray<T>::setMode(const dtkDistributed::Mode& mode)
{
    switch(mode) {
    case dtkDistributed::Local:
        m_handler->setLocalMode();
        break;
    case dtkDistributed::Global:
        m_handler->setGlobalMode();
        break;
    default:
        m_handler->setGlobalMode();
        break;
    }
}

template<typename T> void dtkDistributedArray<T>::clear(void)
{
    return m_handler->clear();
}

template<typename T> bool dtkDistributedArray<T>::empty(void) const
{
    return m_handler->empty();
}

template<typename T> qlonglong dtkDistributedArray<T>::count(void) const
{
    return m_handler->count();
}

template<typename T> void dtkDistributedArray<T>::set(const qlonglong& index, const T& value)
{
    m_handler->set(index, value);
}

template<typename T> T dtkDistributedArray<T>::at(const qlonglong& index) const
{
    return m_handler->at(index);
}

template<typename T> T dtkDistributedArray<T>::first(void) const
{
    return m_handler->first();
}

template<typename T> T dtkDistributedArray<T>::last(void) const
{
    return m_handler->last();
}

template<typename T> dtkDistributedItem<T> dtkDistributedArray<T>::operator [] (const qlonglong& index)
{
    return dtkDistributedItem<T>(new dtkDistributedArrayItem<T>(const_cast<dtkDistributedArray<T>*>(this), index));
}

template<typename T>  dtkDistributedIterator<T> dtkDistributedArray<T>::iterator(void)
{
    return m_handler->iterator();
}

template<typename T>  qlonglong dtkDistributedArray<T>::localToGlobal(const qlonglong& index)
{
    return m_handler->localToGlobal(index);
}

