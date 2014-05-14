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

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::item implementation
// /////////////////////////////////////////////////////////////////

inline dtkMetaContainerSequential::item::item(dtkMetaContainerSequential::iterator *iter) : m_iterator(iter), m_h(iter->m_h)
{

}

inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator = (const item& o)
{
    m_h.setValueToIterator(o.m_h.iteratorValue());
    return *this;
}

inline dtkMetaContainerSequential::item::~item()
{
    if (m_iterator) {
        m_iterator->m_item = NULL;
        delete m_iterator;
    }
}

template<typename T> inline T dtkMetaContainerSequential::item::value(void) const
{
    return (*(*this)).value<T>();
}

template<typename T> inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator = (const T& value)
{
    m_h.setValueToIterator(&value);
    return *this;
}

template<typename T> inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator += (const T& value)
{
    m_h.addValueToIterator(&value);
    return *this;
}

template<typename T> inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator -= (const T& value)
{
    m_h.subValueToIterator(&value);
    return *this;
}

template<typename T> inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator *= (const T& value)
{
    m_h.mulValueToIterator(&value);
    return *this;
}

template<typename T> inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator /= (const T& value)
{
    m_h.divValueToIterator(&value);
    return *this;
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::iterator implementation
// /////////////////////////////////////////////////////////////////

inline bool dtkMetaContainerSequential::iterator::operator == (const iterator& o) const
{
    return (m_h.equal(o.m_h));
}

inline bool dtkMetaContainerSequential::iterator::operator != (const iterator& o) const
{
    return !(m_h.equal(o.m_h));
}

inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::iterator::operator * (void) const
{
    return *m_item;
}

inline dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator ++ (void)
{
    m_h.advance(1);
    return *this;
}

inline dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator -- (void)
{
    m_h.advance(-1);
    return *this;
}

inline dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator += (int j)
{
    m_h.advance(j);
    return *this;
}

inline dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator -= (int j)
{
    m_h.advance(-j);
    return *this;
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::const_iterator implementation
// /////////////////////////////////////////////////////////////////

inline bool dtkMetaContainerSequential::const_iterator::operator == (const const_iterator& o) const
{
    return m_h.equalConst(o.m_h);
}

inline bool dtkMetaContainerSequential::const_iterator::operator != (const const_iterator& o) const
{
    return !(m_h.equalConst(o.m_h));
}

inline dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator ++ (void)
{
    m_h.advanceConst(1);
    return *this;
}

inline dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator -- (void)
{
    m_h.advanceConst(-1);
    return *this;
}

inline dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator += (int j)
{
    m_h.advanceConst(j);
    return *this;
}

inline dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator -= (int j)
{
    m_h.advanceConst(-j);
    return *this;
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential implementation
// /////////////////////////////////////////////////////////////////

inline dtkMetaContainerSequential::dtkMetaContainerSequential(dtkMetaContainerSequentialPrivate::handler h) : m_handler(h) 
{

}

inline bool dtkMetaContainerSequential::hasBiDirectionalIterator(void) const 
{
    return m_handler.m_iterator_capabilities && dtkMetaContainerSequentialPrivate::BiDirectionalCapability;
}

inline bool dtkMetaContainerSequential::hasRandomAccessIterator(void) const 
{
    return m_handler.m_iterator_capabilities && dtkMetaContainerSequentialPrivate::RandomAccessCapability;
}

inline void dtkMetaContainerSequential::clear(void)
{
    m_handler.clear();
}

inline void dtkMetaContainerSequential::reserve(int size)
{
    m_handler.reserve(size);
}

inline void dtkMetaContainerSequential::resize(int size)
{
    m_handler.resize(size);
}

inline bool dtkMetaContainerSequential::empty(void) const 
{
    return const_cast<dtkMetaContainerSequentialPrivate::handler&>(m_handler).empty();
}

inline int dtkMetaContainerSequential::size(void) const 
{
    return const_cast<dtkMetaContainerSequentialPrivate::handler&>(m_handler).size();
}

template<typename T> inline void dtkMetaContainerSequential::setAt(int idx, const T& t) 
{
    m_handler.setAt(idx, &t);
}

template<typename T> inline void dtkMetaContainerSequential::append(const T& t) 
{
    m_handler.insert(this->size(), &t);
}

inline void dtkMetaContainerSequential::append(const QVariant& v) 
{
    this->insert(this->size(), v);
}

template<typename T> inline void dtkMetaContainerSequential::prepend(const T& t) 
{
    m_handler.insert(0, &t);
}

inline void dtkMetaContainerSequential::prepend(const QVariant& v) 
{
    this->insert(0, v);
}

template<typename T> inline void dtkMetaContainerSequential::insert(int idx, const T& t) 
{
    m_handler.insert(idx, &t);
}

inline void dtkMetaContainerSequential::removeAt(int idx) 
{
    m_handler.remove(idx);
}

inline const QVariant dtkMetaContainerSequential::first(void) const 
{
    return this->at(0);
}

inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::first(void)
{
    iterator *it = new iterator(this->m_handler, new QAtomicInt(0));
    it->m_h.moveToBegin();
    return *(*it);
}

inline const QVariant dtkMetaContainerSequential::last(void) const 
{
    return this->at(this->size() - 1);
}

inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::last(void)
{
    iterator *it = new iterator(this->m_handler, new QAtomicInt(0));
    it->m_h.moveToEnd();
    --(*it);
    return *(*it);
}

inline const QVariant dtkMetaContainerSequential::operator [] (int idx) const
{
    return this->at(idx);
}

inline dtkMetaContainerSequential::item& dtkMetaContainerSequential::operator [] (int idx)
{
    iterator *it = new iterator(this->m_handler, new QAtomicInt(0));
    it->m_h.moveToBegin();
    *it += idx;
    return *(*it);
}

// /////////////////////////////////////////////////////////////////
// Specialization of Qt internal struct to build QVariant of dtkMetaContainerSequential
// /////////////////////////////////////////////////////////////////

namespace QtPrivate {
inline dtkMetaContainerSequential QVariantValueHelperInterface<dtkMetaContainerSequential>::invoke(const QVariant &v)
{
    return dtkMetaContainerSequential(v.value<dtkMetaContainerSequentialPrivate::handler>());
}
}

//
// dtkMetaContainerSequential.tpp ends here

