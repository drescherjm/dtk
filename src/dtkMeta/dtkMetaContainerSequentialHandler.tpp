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

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerTemplate
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkMetaContainerSequentialHandlerTemplate<T>::dtkMetaContainerSequentialHandlerTemplate(T *c) : m_container(c)
{
}

template <typename T> inline dtkMetaContainerSequentialHandlerTemplate<T>::~dtkMetaContainerSequentialHandlerTemplate(void)
{ 
    m_container = NULL; 
}

template <typename T> inline bool dtkMetaContainerSequentialHandlerTemplate<T>::hasBiDirectionalIterator(void) const
{
    return dtkMetaContainerSequentialHandlerHelper<T>::hasBidirectionalIterator();
}

template <typename T> inline bool dtkMetaContainerSequentialHandlerTemplate<T>::hasRandomAccessIterator(void) const
{
    return dtkMetaContainerSequentialHandlerHelper<T>::hasRandomAccesIterator();
}

template <typename T> inline bool dtkMetaContainerSequentialHandlerTemplate<T>::empty(void) const
{
    return dtkMetaContainerSequentialHandlerHelper<T>::empty(m_container);
}

template <typename T> inline qlonglong dtkMetaContainerSequentialHandlerTemplate<T>::size(void) const
{
    return dtkMetaContainerSequentialHandlerHelper<T>::size(m_container);
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::clear(void)
{
    dtkMetaContainerSequentialHandlerHelper<T>::clear(m_container);
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::reserve(qlonglong size)
{
    dtkMetaContainerSequentialHandlerHelper<T>::reserve(m_container, size);
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::resize(qlonglong size)
{
    dtkMetaContainerSequentialHandlerHelper<T>::resize(m_container, size);
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::append(const void *t)
{
    dtkMetaContainerSequentialHandlerHelper<T>::insert(m_container, this->size(), *(static_cast<const typename T::value_type *>(t)));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::prepend(const void *t)
{
    dtkMetaContainerSequentialHandlerHelper<T>::insert(m_container, 0, *(static_cast<const typename T::value_type *>(t)));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::insert(qlonglong idx, const void *t)
{
    dtkMetaContainerSequentialHandlerHelper<T>::insert(m_container, idx, *(static_cast<const typename T::value_type *>(t)));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::setAt(qlonglong idx, const void *t)
{
    dtkMetaContainerSequentialHandlerHelper<T>::setAt(m_container, idx, *(static_cast<const typename T::value_type *>(t)));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::removeAt(qlonglong idx)
{
    dtkMetaContainerSequentialHandlerHelper<T>::removeAt(m_container, idx);
}

template <typename T> inline const void *dtkMetaContainerSequentialHandlerTemplate<T>::at(qlonglong idx) const
{
    return dtkMetaContainerSequentialHandlerHelper<T>::at(m_container, idx);
}

template <typename T> inline void *dtkMetaContainerSequentialHandlerTemplate<T>::at(qlonglong idx)
{
    return dtkMetaContainerSequentialHandlerHelper<T>::at(m_container, idx);
}

template <typename T> inline typename dtkMetaContainerSequentialHandlerTemplate<T>::item *dtkMetaContainerSequentialHandlerTemplate<T>::itemAt(qlonglong idx)
{
    return new item(dtkMetaContainerSequentialHandlerHelper<T>::at(m_container, idx));
}

template <typename T> inline QVariant dtkMetaContainerSequentialHandlerTemplate<T>::variantAt(qlonglong idx)
{
    return dtkMetaType::variantFromValue(*dtkMetaContainerSequentialHandlerHelper<T>::at(m_container, idx));
}

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerTemplate item
// ///////////////////////////////////////////////////////////////////

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::item::assign(const void *t)
{
    dtkMetaContainerSequentialItemHelper<ValueType>::assign(*ref, *static_cast<const ValueType *>(t));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::item::addAssign(const void *t)
{
    dtkMetaContainerSequentialItemHelper<ValueType>::addAssign(*ref, *static_cast<const ValueType *>(t));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::item::subAssign(const void *t)
{
    dtkMetaContainerSequentialItemHelper<ValueType>::subAssign(*ref, *static_cast<const ValueType *>(t));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::item::mulAssign(const void *t)
{
    dtkMetaContainerSequentialItemHelper<ValueType>::mulAssign(*ref, *static_cast<const ValueType *>(t));
}

template <typename T> inline void dtkMetaContainerSequentialHandlerTemplate<T>::item::divAssign(const void *t)
{
    dtkMetaContainerSequentialItemHelper<ValueType>::divAssign(*ref, *static_cast<const ValueType *>(t));
}

template <typename T> inline bool dtkMetaContainerSequentialHandlerTemplate<T>::item::equal(const void *t)
{
    return (*ref == *static_cast<const ValueType *>(t));
}

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerHelper
// ///////////////////////////////////////////////////////////////////

template <typename T> inline bool dtkMetaContainerSequentialHandlerHelper<T>::empty(const T *c)
{
    return c->empty();
}

template <typename T> inline qlonglong dtkMetaContainerSequentialHandlerHelper<T>::size(const T *c)
{
    return c->size();
}

template <typename T> inline void dtkMetaContainerSequentialHandlerHelper<T>::clear(T *c)
{
    c->clear();
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaContainerIsReservable<U>::value>::type dtkMetaContainerSequentialHandlerHelper<T>::reserve(T *c, qlonglong size)
{
    c->reserve(size);
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaContainerIsReservable<U>::value>::type dtkMetaContainerSequentialHandlerHelper<T>::reserve(T *, qlonglong)
{
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaContainerIsResizable<U>::value>::type dtkMetaContainerSequentialHandlerHelper<T>::resize(T *c, qlonglong size)
{
    c->resize(size);
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaContainerIsResizable<U>::value>::type dtkMetaContainerSequentialHandlerHelper<T>::resize(T *, qlonglong)
{
}

template <typename T> inline void dtkMetaContainerSequentialHandlerHelper<T>::insert(T *c, qlonglong idx, const ValueType& t)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);    
    c->insert(it, t);
}

template <typename T> inline void dtkMetaContainerSequentialHandlerHelper<T>::setAt(T *c, qlonglong idx, const ValueType& t)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);
    *it = t;
}

template <typename T> inline void dtkMetaContainerSequentialHandlerHelper<T>::removeAt(T *c, qlonglong idx)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);    
    c->erase(it);
}

template <typename T> inline const typename dtkMetaContainerSequentialHandlerHelper<T>::ValueType *dtkMetaContainerSequentialHandlerHelper<T>::at(const T *c, qlonglong idx)
{
    typename T::const_iterator it(c->begin());
    std::advance(it, idx);
    return &(*it);
}

template <typename T> inline typename dtkMetaContainerSequentialHandlerHelper<T>::ValueType *dtkMetaContainerSequentialHandlerHelper<T>::at(T *c, qlonglong idx)
{
    typename T::iterator it(c->begin());
    std::advance(it, idx);
    return &(*it);
}

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialItemHelper
// ///////////////////////////////////////////////////////////////////

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaTypeIsAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::assign(T& lhs, const T& rhs)
{ 
    lhs = rhs; 
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaTypeIsAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::assign(T&, const T&) 
{
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaTypeIsAddAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::addAssign(T& lhs, const T& rhs)
{ 
    lhs += rhs; 
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaTypeIsAddAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::addAssign(T&, const T&) 
{
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaTypeIsSubAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::subAssign(T& lhs, const T& rhs)
{ 
    lhs -= rhs; 
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaTypeIsSubAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::subAssign(T&, const T&) 
{
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaTypeIsMulAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::mulAssign(T& lhs, const T& rhs)
{ 
    lhs *= rhs; 
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaTypeIsMulAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::mulAssign(T&, const T&) 
{
}

template <typename T> template <typename U> inline typename std::enable_if<dtkMetaTypeIsDivAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::divAssign(T& lhs, const T& rhs)
{ 
    lhs /= rhs; 
}

template <typename T> template <typename U> inline typename std::enable_if<!dtkMetaTypeIsDivAssignable<U>::value>::type dtkMetaContainerSequentialItemHelper<T>::divAssign(T&, const T&) 
{
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialConvertFunctor
// /////////////////////////////////////////////////////////////////

template <typename From> inline dtkMetaContainerSequentialHandler *dtkMetaContainerSequentialConvertFunctor<From *>::operator () (From *f) const
{
    return new dtkMetaContainerSequentialHandlerTemplate<From>(f);
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////
    
template <typename T> inline bool dtkMetaType::registerContainerPointerConverter(int id) 
{ 
    return dtkMetaContainerSequentialRegisterConverter<T>::record(id);
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

template <typename T, bool B> inline bool dtkMetaContainerSequentialRegisterConverter<T, B>::record(int id)
{
    return false;
}

template <typename T> inline bool dtkMetaContainerSequentialRegisterConverter<T, true>::record(int id)
{
    const int toId = qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    if (!QMetaType::hasRegisteredConverterFunction(id, toId)) {
        dtkMetaContainerSequentialConvertFunctor<T> o;
        return QMetaType::registerConverter<T ,dtkMetaContainerSequentialHandler *, dtkMetaContainerSequentialConvertFunctor<T> >(o);
    }
    return true;    
}

// 
// dtkMetaContainerSequentialHandler.tpp ends here
