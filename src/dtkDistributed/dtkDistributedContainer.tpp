/* dtkDistributedContainer.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb  4 16:02:53 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTAINER_TPP
#define DTKDISTRIBUTEDCONTAINER_TPP

// /////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedLocalIterator<T>::dtkDistributedLocalIterator(dtkDistributedContainer<T> *container) : c(container), i(c->m_array.constBegin())
{

};
 
template<typename T> dtkDistributedLocalIterator<T>::~dtkDistributedLocalIterator(void)
{

};

template <typename T> void dtkDistributedLocalIterator<T>::toBack(void)
{
    i = c->m_array.constEnd();
};

template <typename T> void dtkDistributedLocalIterator<T>::toFront(void)
{
    i = c->m_array.constBegin();
};

template <typename T> bool dtkDistributedLocalIterator<T>::hasNext(void)
{
    return (i != c->m_array.constEnd());
};

template <typename T> bool dtkDistributedLocalIterator<T>::hasPrevious(void)
{
    return (i != c->m_array.constBegin());
};

template <typename T> const T& dtkDistributedLocalIterator<T>::next(void)
{
    return (*i++);
};

template <typename T> const T& dtkDistributedLocalIterator<T>::previous(void)
{
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
    return 0;
};

template <typename T> qlonglong dtkDistributedLocalIterator<T>::globalIndex(void) const
{
    return 0;
};


// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer implementation
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedContainer<T>::dtkDistributedContainer(void)
{
    m_iterator = NULL;
};

template<typename T> dtkDistributedContainer<T>::~dtkDistributedContainer(void)
{
    if (m_iterator)
        delete m_iterator;

    m_iterator = NULL;
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

template <typename T> dtkDistributedLocalIterator<T> *dtkDistributedContainer<T>::localIterator(void)
{
    if (!m_iterator)
        m_iterator = new dtkDistributedLocalIterator<T>(this);

    return m_iterator;    
};

#endif
