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


#pragma once

#include <QtCore>

#include "dtkDistributedIterator.h"

// ///////////////////////////////////////////////////////////////////
// dtkDistributedNavigator
// ///////////////////////////////////////////////////////////////////

template<typename Container> class dtkDistributedNavigator
{
    const Container& c;
    qlonglong m_start_id;
    qlonglong m_size;

public:
    dtkDistributedNavigator(const Container& container);
    dtkDistributedNavigator(const Container& container, qlonglong start, qlonglong size);

public:
    dtkDistributedNavigator(const dtkDistributedNavigator& other);
    dtkDistributedNavigator(dtkDistributedNavigator&& other);

public:
    dtkDistributedNavigator& operator = (const dtkDistributedNavigator& other);
    dtkDistributedNavigator& operator = (dtkDistributedNavigator&& other);

public:
    void setRange(qlonglong start, qlonglong size);

public:
    qlonglong size(void) const;
    qlonglong startIndex(void) const;

public:
    typedef dtkDistributedIterator<Container> iterator;

public:
    iterator begin(void) const;
    iterator   end(void) const;
};

// ///////////////////////////////////////////////////////////////////

template<typename Container> inline dtkDistributedNavigator<Container>::dtkDistributedNavigator(const Container& container) : c(container), m_start_id(0), m_size(0)
{
}

template<typename Container> inline dtkDistributedNavigator<Container>::dtkDistributedNavigator(const Container& container, qlonglong start, qlonglong size) : c(container), m_start_id(start), m_size(size)
{
}

template<typename Container> inline dtkDistributedNavigator<Container>::dtkDistributedNavigator(const dtkDistributedNavigator<Container>& o) : c(o.c), m_start_id(o.m_start_id), m_size(o.m_size)
{

}

template<typename Container> inline dtkDistributedNavigator<Container>::dtkDistributedNavigator(dtkDistributedNavigator<Container>&& o) : c(o.c), m_start_id(o.m_start_id), m_size(o.m_size)
{

}

template<typename Container> inline dtkDistributedNavigator<Container>& dtkDistributedNavigator<Container>::operator = (const dtkDistributedNavigator<Container>& o)
{
    m_start_id = o.m_start_id;
    m_size = o.m_size;
}

template<typename Container> inline dtkDistributedNavigator<Container>& dtkDistributedNavigator<Container>::operator = (dtkDistributedNavigator<Container>&& o)
{
    m_start_id = o.m_start_id;
    m_size = o.m_size;
}

template<typename Container> inline void dtkDistributedNavigator<Container>::setRange(qlonglong start, qlonglong size)
{
    m_start_id = start;
    m_size = size;
}

template<typename Container> inline qlonglong dtkDistributedNavigator<Container>::size(void) const
{
    return m_size;
}

template<typename Container> inline qlonglong dtkDistributedNavigator<Container>::startIndex(void) const
{
    return m_start_id;
}

template<typename Container> inline typename dtkDistributedNavigator<Container>::iterator dtkDistributedNavigator<Container>::begin(void) const
{
    return iterator(c, m_start_id);
}

template<typename Container> inline typename dtkDistributedNavigator<Container>::iterator dtkDistributedNavigator<Container>::end(void) const
{
    return iterator(c, m_start_id + m_size);
}

// 
// dtkDistributedNavigator.h ends here
