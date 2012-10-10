/* dtkContainerVectorWrapper.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri May 25 09:47:39 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 10 12:16:07 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 58
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

template <typename T> dtkContainerVectorWrapper<T>::dtkContainerVectorWrapper(void) : dtkAbstractContainerWrapper()
{
    this->init(this);
};

template <typename T> dtkContainerVectorWrapper<T>::dtkContainerVectorWrapper(dtkContainerVector<T> *vector) : dtkAbstractContainerWrapper(), m_vector(vector)
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
    m_vector = NULL;
};

template <typename T> dtkContainerVectorWrapper<T>& dtkContainerVectorWrapper<T>::operator = (const dtkContainerVectorWrapper<T>& other)
{
    dtkAbstractData::operator = (other);

    m_vector = other.m_vector;
    
    return *this;
};

template <typename T> dtkContainerVectorWrapper<T> *dtkContainerVectorWrapper<T>::clone(void)
{
    return new dtkContainerVectorWrapper<T>(*this);
};

template <typename T> dtkContainerVectorWrapper<T> *dtkContainerVectorWrapper<T>::voidClone(void)
{
    // hack
    dtkContainerVector<T> *vec = new dtkContainerVector<T>();
    return new dtkContainerVectorWrapper<T>(vec);
};

template <typename T> QString dtkContainerVectorWrapper<T>::identifier(void) const
{
    return QString("dtkContainerVectorWrapper<%1>").arg(typeid(T).name());
};

template <typename T> QString dtkContainerVectorWrapper<T>::description(void) const
{
    if (m_vector)
        return m_vector->description();

    return QString("dtkContainerVectorWrapper<%1> is void! It might not be what you expect.").arg(typeid(T).name());
};

template <typename T> inline void dtkContainerVectorWrapper<T>::setVector(dtkContainerVector<T> *vector)
{
    m_vector = vector;
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVectorWrapper<T>::vector(void)
{
    return m_vector;
};

template <typename T> dtkAbstractContainerWrapper::Type dtkContainerVectorWrapper<T>::type(void) const
{
    return dtkAbstractContainerWrapper::Vector;
};

template <typename T> inline void dtkContainerVectorWrapper<T>::clear(void)
{
    m_vector->clear();
};

template <typename T> inline void dtkContainerVectorWrapper<T>::append(const QVariant& data)
{
    m_vector->append(data.value<T>());
};

template <typename T> inline void dtkContainerVectorWrapper<T>::prepend(const QVariant& data)
{
    m_vector->prepend(data.value<T>());
};

template <typename T> void dtkContainerVectorWrapper<T>::remove(const QVariant& data)
{
    m_vector->remove(data.value<T>());
};

template <typename T> inline void dtkContainerVectorWrapper<T>::insert(const QVariant& data, qlonglong index)
{
    m_vector->insert(index, data.value<T>());
};

template <typename T> inline void dtkContainerVectorWrapper<T>::replace(const QVariant& data, qlonglong index)
{
    m_vector->replace(index, data.value<T>());
};

template <typename T> inline void dtkContainerVectorWrapper<T>::resize(qlonglong size)
{
    m_vector->reserve(size);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::isEmpty(void) const
{
    return m_vector->isEmpty();
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::contains(const QVariant& data) const
{
    return m_vector->contains(data.value<T>());
};

template <typename T> inline qlonglong dtkContainerVectorWrapper<T>::count(void) const
{
    return m_vector->count();
};

template <typename T> inline qlonglong dtkContainerVectorWrapper<T>::indexOf(const QVariant& data, qlonglong from) const
{
    return m_vector->indexOf(data.value<T>(), from);
};

template <typename T> inline QVariant dtkContainerVectorWrapper<T>::at(qlonglong index) const
{
    return qVariantFromValue(m_vector->at(index));
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::operator != (const dtkContainerVectorWrapper<T>& other) const
{
    return (*m_vector != *other.m_vector);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::operator == (const dtkContainerVectorWrapper<T>& other) const
{
    return (*m_vector == *other.m_vector);
};

template <typename T> inline bool dtkContainerVectorWrapper<T>::isEqual(const dtkAbstractObject& other) const
{
    if (this == &other)
        return true;

    if (this->identifier() != other.identifier())
        return false;

    const dtkAbstractContainerWrapper& wrapper = reinterpret_cast<const dtkAbstractContainerWrapper&>(other);

    if (wrapper.type() == Vector) {
        if (const dtkContainerVectorWrapper<T> *other_v = dynamic_cast<const dtkContainerVectorWrapper<T> *>(&wrapper)) {
            return (*m_vector == *other_v->m_vector);
        }
    }

    return false;
};

#endif
