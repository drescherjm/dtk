/* dtkContainerVector.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 17:02:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun May  6 16:23:40 2012 (+0200)
 *           By: tkloczko
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTOR_TPP
#define DTKCONTAINERVECTOR_TPP

// /////////////////////////////////////////////////////////////////
// dtkContainerVector implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkContainerVector<T>::dtkContainerVector(dtkAbstractData *parent) : dtkAbstractContainer(parent)
{

};

template <typename T> dtkContainerVector<T>::dtkContainerVector(const QVector<T>& vector, dtkAbstractData *parent) : dtkAbstractContainer(parent), m_vector(vector)
{

};

template <typename T> dtkContainerVector<T>::dtkContainerVector(const dtkContainerVector& other) : dtkAbstractContainer(other), m_vector(other.m_vector)
{

};

template <typename T> dtkContainerVector<T>::~dtkContainerVector(void)
{

};

template <typename T> dtkContainerVector<T>& dtkContainerVector<T>::operator = (const dtkContainerVector<T>& other)
{
    dtkAbstractContainer::operator=(other);

    m_vector = other.m_vector;
    
    return *this;
};

template <typename T> inline void dtkContainerVector<T>::setVector(const QVector<T>& vector)
{
    m_vector = vector;
};

template <typename T> inline QVector<T>& dtkContainerVector<T>::vector(void)
{
    return m_vector;
};

template <typename T> dtkAbstractContainer::Type dtkContainerVector<T>::type(void) const
{
    return dtkAbstractContainer::Vector;
};

template <typename T> inline void dtkContainerVector<T>::clear(void)
{
    m_vector.clear();
};

template <typename T> inline void dtkContainerVector<T>::append(const QVariant& data)
{
    m_vector.append(qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVector<T>::prepend(const QVariant& data)
{
    m_vector.prepend(qvariant_cast<T>(data));
};

template <typename T> void dtkContainerVector<T>::remove(const QVariant& data)
{
    T t = qvariant_cast<T>(data);
    dtkxarch_int index = m_vector.indexOf(t);
    while (index >= 0) {
        m_vector.remove(index);
        index = m_vector.indexOf(t);
    }
};

template <typename T> inline void dtkContainerVector<T>::insert(const QVariant& data, dtkxarch_int index)
{
    m_vector.insert(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVector<T>::replace(const QVariant& data, dtkxarch_int index)
{
    m_vector.replace(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerVector<T>::resize(dtkxarch_int size)
{
    m_vector.resize(size);
};

template <typename T> inline bool dtkContainerVector<T>::isEmpty(void) const
{
    return m_vector.isEmpty();
};

template <typename T> inline bool dtkContainerVector<T>::contains(const QVariant& data) const
{
    return m_vector.contains(qvariant_cast<T>(data));
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::count(void) const
{
    return m_vector.count();
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::indexOf(const QVariant& data, dtkxarch_int from) const
{
    return m_vector.indexOf(qvariant_cast<T>(data), from);
};

template <typename T> inline QVariant dtkContainerVector<T>::at(dtkxarch_int index) const
{
    return qvariantFromValue(m_vector.at(index));
};

template <typename T> inline QVariant dtkContainerVector<T>::first(void) const
{
    return qvariantFromValue(m_vector.first(index));
};

template <typename T> inline QVariant dtkContainerVector<T>::last(void) const
{
    return qvariantFromValue(m_vector.last(index));
};

template <typename T> inline bool dtkContainerVector<T>::operator != (const dtkAbstractContainer& other) const
{
    if (other.type() == Vector) {
        if (dtkContainerVector<T> other_v = dynamic_cast<dtkContainerVector<T> >(other)) { 
            return (m_vector != other_v.m_vector);
        }
    }

    return true;
};

template <typename T> inline bool dtkContainerVector<T>::operator == (const dtkAbstractContainer& other) const
{
    if (other.type() == Vector) {
        if (dtkContainerVector<T> other_v = dynamic_cast<dtkContainerVector<T> >(other)) { 
            return (m_vector == other_v.m_vector);
        }
    }

    return false;
};

template <typename T> inline QVariant dtkContainerVector<T>::operator[] (dtkxarch_int index) const
{
    return qvariantFromValue(m_vector[index]);
};

#endif
