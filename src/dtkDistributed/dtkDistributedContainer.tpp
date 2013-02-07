/* dtkDistributedContainer.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:12:49 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb  7 15:07:57 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 56
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkDistributedMapper.h"

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

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(void) : m_iterator(0), m_mapper(new dtkDistributedMapper), m_comm(0)
{
    
};

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(const qlonglong& size, dtkDistributedCommunicator *communicator) : m_iterator(0), m_mapper(new dtkDistributedMapper), m_comm(communicator)
{
    this->resize(size);

    //m_mapper->setMapping(size, m_comm->size());
};

template<typename T> dtkDistributedContainer<T>::~dtkDistributedContainer(void)
{
    delete m_iterator;
    delete m_mapper;
};

template<typename T> void dtkDistributedContainer<T>::resize(const qlonglong& size)
{
    m_array.resize(size);
};

template <typename T> qlonglong dtkDistributedContainer<T>::size(void) const
{
    return m_array.size();
};

template <typename T> void dtkDistributedContainer<T>::set(const qlonglong& index, const T& value)
{
    m_array.replace(index, value);
};

template <typename T> const T&dtkDistributedContainer<T>:: at(const qlonglong& index)
{
    return m_array.at(index);
};

template <typename T> dtkDistributedLocalIterator<T>& dtkDistributedContainer<T>::localIterator(void)
{
    if (!m_iterator)
        m_iterator = new dtkDistributedLocalIterator<T>(*this);

    return *m_iterator;
};
