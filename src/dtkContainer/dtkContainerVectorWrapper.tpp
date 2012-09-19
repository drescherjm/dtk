/* dtkContainerVectorWrapper.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri May 25 09:47:39 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jul  4 12:21:44 2012 (+0200)
 *           By: tkloczko
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTORWRAPPER_TPP
#define DTKCONTAINERVECTORWRAPPER_TPP

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorWrapper implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkContainerVectorWrapper<T>::dtkContainerVectorWrapper(dtkAbstractData *parent) : dtkAbstractContainerWrapper(parent)
{
    this->init(this);
};

template <typename T> dtkContainerVectorWrapper<T>::dtkContainerVectorWrapper(const dtkContainerVector<T>& vector, dtkAbstractData *parent) : dtkAbstractContainerWrapper(parent), m_vector(vector)
{
    this->init(this);
};

template <typename T> dtkContainerVectorWrapper<T>::dtkContainerVectorWrapper(const dtkContainerVectorWrapper& other) : dtkAbstractContainerWrapper(), m_vector(other.m_vector)
{
    dtkAbstractData::operator=(other);
    this->init(this);
};

template <typename T> dtkContainerVectorWrapper<T>::~dtkContainerVectorWrapper(void)
{

};

template <typename T> dtkContainerVectorWrapper<T>& dtkContainerVectorWrapper<T>::operator = (const dtkContainerVectorWrapper<T>& other)
{
    dtkAbstractData::operator=(other);

    m_vector = other.m_vector;
    
    return *this;
};

template <typename T> dtkContainerVectorWrapper<T> *dtkContainerVectorWrapper<T>::clone(void) const
{
    return new dtkContainerVectorWrapper<T>(*this);
};

template <typename T> dtkContainerVectorWrapper<T> *dtkContainerVectorWrapper<T>::voidClone(void) const
{
    return new dtkContainerVectorWrapper<T>();
};

template <typename T> QString dtkContainerVectorWrapper<T>::identifier(void) const
{
    return "dtkContainerVectorWrapper";
};

template <typename T> inline void dtkContainerVectorWrapper<T>::setVector(const dtkContainerVector<T>& vector)
{
    m_vector = vector;
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVectorWrapper<T>::vector(void)
{
    return m_vector;
};

template <typename T> inline const dtkContainerVector<T>& dtkContainerVectorWrapper<T>::vector(void) const
{
    return m_vector;
};

template <typename T> dtkAbstractContainerWrapper::Type dtkContainerVectorWrapper<T>::type(void) const
{
    return dtkAbstractContainerWrapper::Vector;
};

template <typename T> inline void dtkContainerVectorWrapper<T>::clear(void)
{
    m_vector.clear();
};

template <typename T> inline void dtkContainerVectorWrapper<T>::append(const QVariant& data)
{
    m_vector.append(qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVectorWrapper<T>::prepend(const QVariant& data)
{
    m_vector.prepend(qvariant_cast<T>(data));
};

template <typename T> void dtkContainerVectorWrapper<T>::remove(const QVariant& data)
{
    m_vector.remove(qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVectorWrapper<T>::insert(const QVariant& data, qlonglong index)
{
    m_vector.insert(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVectorWrapper<T>::replace(const QVariant& data, qlonglong index)
{
    m_vector.replace(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVectorWrapper<T>::resize(qlonglong size)
{
    m_vector.reserve(size);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::isEmpty(void) const
{
    return m_vector.isEmpty();
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::contains(const QVariant& data) const
{
    return m_vector.contains(qvariant_cast<T>(data));
};

template <typename T> inline qlonglong dtkContainerVectorWrapper<T>::count(void) const
{
    return m_vector.count();
};

template <typename T> inline qlonglong dtkContainerVectorWrapper<T>::indexOf(const QVariant& data, qlonglong from) const
{
    return m_vector.indexOf(qvariant_cast<T>(data), from);
};

template <typename T> inline QVariant dtkContainerVectorWrapper<T>::at(qlonglong index) const
{
    return qVariantFromValue(m_vector.at(index));
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::operator != (const dtkContainerVectorWrapper<T>& other) const
{
    return (m_vector != other.m_vector);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::operator == (const dtkContainerVectorWrapper<T>& other) const
{
    return (m_vector == other.m_vector);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::isEqual(const dtkAbstractContainerWrapper& other) const
{
    if (other.type() == Vector) {
        if (const dtkContainerVectorWrapper<T> *other_v = dynamic_cast<const dtkContainerVectorWrapper<T> *>(&other)) {
            return (m_vector == other_v->m_vector);
        }
    }

    return false;
};

#endif
