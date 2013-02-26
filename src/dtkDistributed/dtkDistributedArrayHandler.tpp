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

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkDistributedArrayHandler<T>::initialize(dtkDistributedCommunicator *communicator, const qlonglong& wid, const qlonglong& count, const qlonglong& buffer_count, const qlonglong& buffer_id) 
{
    m_comm = communicator;
    m_wid = wid;
    m_count = count;
    m_buffer_count = buffer_count;
    m_buffer_id = buffer_id;

    m_buffer = static_cast<T*>(m_comm->allocate(m_buffer_count, sizeof(T), m_wid, m_buffer_id));
}

template <typename T> void dtkDistributedArrayHandler<T>::setLocalMode(void) 
{
    clearMethod = &dtkDistributedArrayHandler<T>::clearLocal;
    emptyMethod = &dtkDistributedArrayHandler<T>::emptyLocal;
    countMethod = &dtkDistributedArrayHandler<T>::countLocal;
}

template <typename T> void dtkDistributedArrayHandler<T>::setGlobalMode(void) 
{
    clearMethod = &dtkDistributedArrayHandler<T>::clearGlobal;
    emptyMethod = &dtkDistributedArrayHandler<T>::emptyGlobal;
    countMethod = &dtkDistributedArrayHandler<T>::countGlobal;
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
