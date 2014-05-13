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

#include "dtkMetaContainerSequential.h"

namespace dtkMetaContainerSequentialPrivate
{
// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::iterator implementation
// /////////////////////////////////////////////////////////////////

template<typename I, typename V> inline void iterator<I, V>::assign(void *& ptr, const I& it)
{
    ptr = new I(it);
}

template<typename I, typename V> inline void iterator<I, V>::assign(void *& ptr, void *const& src)
{
    ptr = new I(*static_cast<I *>(src));
}
    
template<typename I, typename V> inline void iterator<I, V>::advance(void *& it, int step)
{
    I& ite = *static_cast<I *>(it);
    std::advance(ite, step);
}

template<typename I, typename V> inline const void *iterator<I, V>::data(void *const & it)
{
    return &**static_cast<I *>(it);
}

template<typename I, typename V> inline const void *iterator<I, V>::data(I& it)
{
    return &*it;
}

template<typename I, typename V> inline void iterator<I, V>::destroy(void *& it)
{
    delete static_cast<I *>(it);
}

template<typename I, typename V> inline int iterator<I, V>::distance(I& from, void *const& to)
{
    return std::distance(from, *(static_cast<I *>(to)));
}

template<typename I, typename V> inline bool iterator<I, V>::equal(void *it, void *other)
{
    return *static_cast<I *>(it) == *static_cast<I *>(other);
}

template<typename I, typename V> inline void iterator<I, V>::setData(void *& it, const void *value)
{
    **static_cast<I *>(it) = *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iterator<I, V>::setData(I& it, const void *value)
{
    *it = *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iterator<I, V>::add(void *& it, const void *value)
{
    **static_cast<I *>(it) += *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iterator<I, V>::sub(void *& it, const void *value)
{
    **static_cast<I *>(it) -= *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iterator<I, V>::mul(void *& it, const void *value)
{
    **static_cast<I *>(it) *= *static_cast<const V *>(value);
}

template<typename I, typename V> inline void iterator<I, V>::div(void *& it, const void *value)
{
    **static_cast<I *>(it) /= *static_cast<const V *>(value);
}

// /////////////////////////////////////////////////////////////////

template<typename V> inline void iterator<V *, V>::assign(void *& ptr, V *const it)
{
    ptr = const_cast<V *>(it);
}

template<typename V> inline void iterator<V *, V>::assign(void *& ptr, void *const& src)
{
    ptr = static_cast<V *>(src);
}
    
template<typename V> inline void iterator<V *, V>::advance(void *& it, int step)
{
    V * ite = static_cast<V *>(it);
    std::advance(ite, step);
    it = ite;
}

template<typename V> inline const void *iterator<V *, V>::data(void *const& it)
{
    return it;
}

template<typename V> inline const void *iterator<V *, V>::data(V *it)
{
    return it;
}

template<typename V> inline void iterator<V *, V>::destroy(void *&)
{
    
}

template<typename V> inline int iterator<V *, V>::distance(V *from, void *const& to)
{
    return std::distance(from, (static_cast<V *>(to)));
}

template<typename V> inline bool iterator<V *, V>::equal(void *it, void *other)
{
    return static_cast<V *>(it) == static_cast<V *>(other);
}

template<typename V> inline void iterator<V *, V>::setData(void *& it, const void *value)
{
    *static_cast<V *>(it) = *static_cast<const V *>(value);
}

template<typename V> inline void iterator<V *, V>::setData(V *it, const void *value)
{
    *it = *static_cast<const V *>(value);
}

template<typename V> inline void iterator<V *, V>::add(void *& it, const void *value)
{
    *static_cast<V *>(it) += *static_cast<const V *>(value);
}

template<typename V> inline void iterator<V *, V>::sub(void *& it, const void *value)
{
    *static_cast<V *>(it) -= *static_cast<const V *>(value);
}

template<typename V> inline void iterator<V *, V>::mul(void *& it, const void *value)
{
    *static_cast<V *>(it) *= *static_cast<const V *>(value);
}

template<typename V> inline void iterator<V *, V>::div(void *& it, const void *value)
{
    *static_cast<V *>(it) /= *static_cast<const V *>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::containerAPI implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline bool containerAPI<T>::empty(const T *c)
{
    return c->empty();
}

template<typename T> inline int containerAPI<T>::size(const T *c)
{
    return c->size();
}

template<typename T> inline void containerAPI<T>::insertData(T *c, int idx, const void *value)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);    
    c->insert(it, *static_cast<const typename T::value_type *>(value));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::handler template method implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline bool handler::emptyPrivate(void *c)
{
    return containerAPI<T>::empty(static_cast<T *>(c));
}

template<typename T> inline int handler::sizePrivate(void *c)
{
    return containerAPI<T>::size(static_cast<T *>(c));
}

template<typename T> inline void handler::setAtPrivate(void *c, int idx, const void *val)
{
    typename T::iterator it = static_cast<T *>(c)->begin();
    std::advance(it, idx);
    iterator<typename T::iterator, typename T::value_type>::setData(it, val);
}

template<typename T> inline void handler::insertPrivate(void *c, int idx, const void *val)
{
    containerAPI<T>::insertData(static_cast<T *>(c), idx, val);
}

template<typename T> inline const void *handler::atPrivate(const void *c, int idx)
{
    typename T::const_iterator it = static_cast<const T *>(c)->begin();
    std::advance(it, idx);
    return iterator<typename T::const_iterator, typename T::value_type>::data(it);
}
    
template<typename T> inline void handler::moveToBeginPrivate(void *c, void *& it)
{
    iterator<typename T::iterator, typename T::value_type>::assign(it, static_cast<T *>(c)->begin());
}
    
template<typename T> inline void handler::moveToCBeginPrivate(void *c, void *& it)
{
    const void *cc = c;
    iterator<typename T::const_iterator, typename T::value_type>::assign(it, static_cast<const T *>(cc)->begin());
}

template<typename T> inline void handler::moveToEndPrivate(void *c, void *& it)
{
    iterator<typename T::iterator, typename T::value_type>::assign(it, static_cast<T *>(c)->end());
}

template<typename T> inline void handler::moveToCEndPrivate(void *c, void *& it)
{
    const void *cc = c;
    iterator<typename T::const_iterator, typename T::value_type>::assign(it, static_cast<const T *>(cc)->end());
}

template<typename T> inline void handler::destroyIteratorPrivate(void *& it)
{
    iterator<typename T::iterator, typename T::value_type>::destroy(it);
}

template<typename T> inline void handler::destroyConstIteratorPrivate(void *& it)
{
    iterator<typename T::const_iterator, typename T::value_type>::destroy(it);
}

template<typename T> inline bool handler::equalIteratorPrivate(void *it, void *o)
{
    return iterator<typename T::iterator, typename T::value_type>::equal(it, o);
}

template<typename T> inline bool handler::equalConstIteratorPrivate(void *it, void *o)
{
    return iterator<typename T::const_iterator, typename T::value_type>::equal(it, o);
}

template<typename T> inline void handler::copyIteratorPrivate(void *& it, void *const& o)
{
    iterator<typename T::iterator, typename T::value_type>::assign(it, o);
}

template<typename T> inline void handler::copyConstIteratorPrivate(void *& it, void *const& o)
{
    iterator<typename T::const_iterator, typename T::value_type>::assign(it, o);
}

template<typename T> inline void handler::advancePrivate(void *& it, int step)
{
    iterator<typename T::iterator, typename T::value_type>::advance(it, step);
}

template<typename T> inline void handler::advanceConstPrivate(void *& it, int step)
{
    iterator<typename T::const_iterator, typename T::value_type>::advance(it, step);
}

template<typename T> inline Data handler::getDataPrivate(void *const& it, int metaTypeId, uint flags)
{
    return Data(metaTypeId, iterator<typename T::iterator, typename T::value_type>::data(it), flags);
}

template<typename T> inline Data handler::getConstDataPrivate(void *const& it, int metaTypeId, uint flags)
{
    return Data(metaTypeId, iterator<typename T::const_iterator, typename T::value_type>::data(it), flags);
}

template<typename T> inline const void *handler::iteratorValuePrivate(void *const& it)
{
    return iterator<typename T::iterator, typename T::value_type>::data(it);
}

template<typename T> inline void handler::setValueToIteratorPrivate(void *& it, const void *val)
{
    iterator<typename T::iterator, typename T::value_type>::setData(it, val);
}

template<typename T> inline void handler::addValueToIteratorPrivate(void *& it, const void *val)
{
    iterator<typename T::iterator, typename T::value_type>::add(it, val);
}

template<typename T> inline void handler::subValueToIteratorPrivate(void *& it, const void *val)
{
    iterator<typename T::iterator, typename T::value_type>::sub(it, val);
}

template<typename T> inline void handler::mulValueToIteratorPrivate(void *& it, const void *val)
{
    iterator<typename T::iterator, typename T::value_type>::mul(it, val);
}

template<typename T> inline void handler::divValueToIteratorPrivate(void *& it, const void *val)
{
    iterator<typename T::iterator, typename T::value_type>::div(it, val);
}

template<typename T> inline int handler::indexOfIteratorPrivate(void *c, void *const& it)
{
    typename T::iterator from = static_cast<T *>(c)->begin();
    return iterator<typename T::iterator, typename T::value_type>::distance(from, it);
}

template<typename T> inline int handler::indexOfConstIteratorPrivate(void *c, void *const& it)
{
    const void *cc = c;
    typename T::const_iterator from = static_cast<const T *>(cc)->begin();
    return iterator<typename T::const_iterator, typename T::value_type>::distance(from, it);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::handler implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline handler::handler(T *c) : m_container(c),
                                                     m_iterator(0),
                                                     m_metaType_id(qMetaTypeId<typename T::value_type>()),
                                                     m_metaType_flags(QTypeInfo<typename T::value_type>::isPointer),
                                                     m_iterator_capabilities(containerAPI<T>::IteratorCapabilities),
                                                     m_empty(emptyPrivate<T>),
                                                     m_size(sizePrivate<T>),
                                                     m_setAt(setAtPrivate<T>),
                                                     m_insert(insertPrivate<T>),
                                                     m_at(atPrivate<T>),
                                                     m_advance(advancePrivate<T>),
                                                     m_advanceConst(advanceConstPrivate<T>),
                                                     m_getData(getDataPrivate<T>),
                                                     m_getConstData(getConstDataPrivate<T>),
                                                     m_moveToBegin(moveToBeginPrivate<T>),
                                                     m_moveToCBegin(moveToCBeginPrivate<T>),
                                                     m_moveToEnd(moveToEndPrivate<T>),
                                                     m_moveToCEnd(moveToCEndPrivate<T>),
                                                     m_destroyIterator(destroyIteratorPrivate<T>),
                                                     m_destroyConstIterator(destroyConstIteratorPrivate<T>),
                                                     m_equalIterator(equalIteratorPrivate<T>),
                                                     m_equalConstIterator(equalConstIteratorPrivate<T>),
                                                     m_copyIterator(copyIteratorPrivate<T>),
                                                     m_copyConstIterator(copyConstIteratorPrivate<T>),
                                                     m_iteratorValue(iteratorValuePrivate<T>),
                                                     m_setValueToIterator(setValueToIteratorPrivate<T>),
                                                     m_addValueTotIterator(addValueToIteratorPrivate<T>),
                                                     m_subValueTotIterator(subValueToIteratorPrivate<T>),
                                                     m_mulValueTotIterator(mulValueToIteratorPrivate<T>),
                                                     m_divValueTotIterator(divValueToIteratorPrivate<T>),
                                                     m_indexOfIterator(indexOfIteratorPrivate<T>),
                                                     m_indexOfConstIterator(indexOfConstIteratorPrivate<T>)
{
}

handler::handler(void) : m_container(0),
                         m_iterator(0),
                         m_metaType_id(QMetaType::UnknownType),
                         m_metaType_flags(0),
                         m_iterator_capabilities(0),
                         m_empty(0),
                         m_size(0),
                         m_setAt(0),
                         m_insert(0),
                         m_at(0),
                         m_advance(0),
                         m_advanceConst(0),
                         m_getData(0),
                         m_getConstData(0),
                         m_moveToBegin(0),
                         m_moveToCBegin(0),
                         m_moveToEnd(0),
                         m_moveToCEnd(0),
                         m_destroyIterator(0),
                         m_destroyConstIterator(0),
                         m_equalIterator(0),
                         m_equalConstIterator(0),
                         m_copyIterator(0),
                         m_copyConstIterator(0),
                         m_iteratorValue(0),
                         m_setValueToIterator(0),
                         m_addValueTotIterator(0),
                         m_subValueTotIterator(0),
                         m_mulValueTotIterator(0),
                         m_divValueTotIterator(0),
                         m_indexOfIterator(0),
                         m_indexOfConstIterator(0)
{
}
inline bool handler::empty(void)
{
    return this->m_empty(m_container);
}

inline int handler::size(void)
{
    return this->m_size(m_container);
}

inline void handler::setAt(int idx, const void *val)
{ 
    this->m_setAt(m_container, idx, val); 
}

inline void handler::insert(int idx, const void *val)
{ 
    this->m_insert(m_container, idx, val);
}

inline handler::Data handler::at(int idx) const
{ 
    return Data(m_metaType_id, this->m_at(m_container, idx), m_metaType_flags);
}

Data handler::currentData(void) const
{
    return this->m_getData(m_iterator, m_metaType_id, m_metaType_flags);
}

Data handler::currentConstData(void) const
{
    return this->m_getConstData(m_iterator, m_metaType_id, m_metaType_flags);
}

handler& handler::advance(int step)
{
    this->m_advance(m_iterator, step);
    return *this;
}

handler& handler::advanceConst(int step)
{
    this->m_advanceConst(m_iterator, step);
    return *this;
}

inline void handler::moveToBegin(void)
{ 
    this->m_moveToBegin(m_container, m_iterator);
}

inline void handler::moveToCBegin(void)
{ 
    this->m_moveToCBegin(m_container, m_iterator);
}

inline void handler::moveToEnd(void)
{ 
    this->m_moveToEnd(m_container, m_iterator);
}

inline void handler::moveToCEnd(void)
{ 
    this->m_moveToCEnd(m_container, m_iterator);
}

inline void handler::destroyIterator(void)
{ 
    this->m_destroyIterator(m_iterator);
}

inline void handler::destroyConstIterator(void)
{ 
    this->m_destroyConstIterator(m_iterator);
}

inline bool handler::equal(const handler& o) const
{ 
    return this->m_equalIterator(m_iterator, o.m_iterator);
}

inline bool handler::equalConst(const handler& o) const
{ 
    return this->m_equalConstIterator(m_iterator, o.m_iterator);
}

inline void handler::copy(const handler& o)
{ 
    *this = o;
    this->m_copyIterator(m_iterator, o.m_iterator);
}

inline void handler::copyConst(const handler& o)
{ 
    *this = o;
    this->m_copyConstIterator(m_iterator, o.m_iterator);
}

inline void handler::setValueToIterator(const void *value)
{
    this->m_setValueToIterator(m_iterator, value);
}

inline void handler::addValueToIterator(const void *value)
{
    this->m_addValueTotIterator(m_iterator, value);
}

inline void handler::subValueToIterator(const void *value)
{
    this->m_subValueTotIterator(m_iterator, value);
}

inline void handler::mulValueToIterator(const void *value)
{
    this->m_mulValueTotIterator(m_iterator, value);
}

inline void handler::divValueToIterator(const void *value)
{
    this->m_divValueTotIterator(m_iterator, value);
}

inline const void *handler::iteratorValue(void) const
{
    return this->m_iteratorValue(m_iterator);
}

inline int handler::indexOfIterator(void) const
{
    return this->m_indexOfIterator(m_container, m_iterator);
}

inline int handler::indexOfConstIterator(void) const
{
    return this->m_indexOfConstIterator(m_container, m_iterator);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::convertFunctor for QMetatype system
// /////////////////////////////////////////////////////////////////

template<typename From> handler convertFunctor::operator () (From *f) const
{
    return handler(f);
}

// /////////////////////////////////////////////////////////////////

} // end of dtkMetaContainerSequentialPrivate namespace

// /////////////////////////////////////////////////////////////////
// Redifinition of Qt helper classes to handle our meta containers
// /////////////////////////////////////////////////////////////////

namespace QtPrivate {
    template<> struct QVariantValueHelperInterface<dtkMetaContainerSequential>
    {
        static dtkMetaContainerSequential invoke(const QVariant &v)
        {
            return dtkMetaContainerSequential(v.value<dtkMetaContainerSequentialPrivate::handler>());
        }
    };
    
    template<typename T> struct SequentialContainerConverterHelper<T *, false>
    {
        static bool registerConverter(int) { return false; }
    };
    
    template<typename T> struct SequentialContainerConverterHelper<T *, true> : ValueTypeIsMetaType<T *, QMetaTypeId2<typename T::value_type>::Defined>
    {
    };
    
    template<typename T> struct ValueTypeIsMetaType<T *, false>
    {
        static bool registerConverter(int) { return false; }
    };
    
    template<typename T> struct ValueTypeIsMetaType<T *, true>
    {
        static bool registerConverter(int id)
        {
            const int toId = qMetaTypeId<dtkMetaContainerSequentialPrivate::handler>();
            if (!QMetaType::hasRegisteredConverterFunction(id, toId)) {
                dtkMetaContainerSequentialPrivate::convertFunctor<T *> o;
                static const QtPrivate::ConverterFunctor<T *,
                                                         dtkMetaContainerSequentialPrivate::handler,
                                                         dtkMetaContainerSequentialPrivate::convertFunctor<T *> > f(o);
                return QMetaType::registerConverterFunction(&f, id, toId);
            }
            return true;
        }
    };
}

//
// dtkMetaContainerSequential.tpp ends here

