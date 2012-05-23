/* dtkContainerList.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sun May  6 15:56:38 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 15:44:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERLIST_TPP
#define DTKCONTAINERLIST_TPP

// /////////////////////////////////////////////////////////////////
// dtkContainerList implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkContainerList<T>::dtkContainerList(dtkAbstractData *parent) : dtkAbstractContainer(parent)
{

};

template <typename T> dtkContainerList<T>::dtkContainerList(const QList<T>& list, dtkAbstractData *parent) : dtkAbstractContainer(parent), m_list(list)
{

};

template <typename T> dtkContainerList<T>::dtkContainerList(const dtkContainerList& other) : dtkAbstractContainer(), m_list(other.m_list)
{
    dtkAbstractData::operator=(other);
    this->init();
};

template <typename T> dtkContainerList<T>::~dtkContainerList(void)
{

};

template <typename T> dtkContainerList<T>& dtkContainerList<T>::operator = (const dtkContainerList<T>& other)
{
    dtkAbstractContainer::operator=(other);

    m_list = other.m_list;
    
    return *this;
};

template <typename T> dtkContainerList<T> *dtkContainerList<T>::clone(void) const
{
    return new dtkContainerList<T>(*this);
};

template <typename T> inline void dtkContainerList<T>::setList(const QList<T>& list)
{
    m_list = list;
};

template <typename T> inline QList<T>& dtkContainerList<T>::list(void)
{
    return m_list;
};

template <typename T> dtkAbstractContainer::Type dtkContainerList<T>::type(void) const
{
    return dtkAbstractContainer::List;
};

template <typename T> inline void dtkContainerList<T>::clear(void)
{
    m_list.clear();
};

template <typename T> inline void dtkContainerList<T>::append(const QVariant& data)
{
    m_list.append(qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerList<T>::prepend(const QVariant& data)
{
    m_list.prepend(qvariant_cast<T>(data));
};

template <typename T> void dtkContainerList<T>::remove(const QVariant& data)
{
    m_list.removeAll(qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerList<T>::insert(const QVariant& data, dtkxarch_int index)
{
    m_list.insert(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerList<T>::replace(const QVariant& data, dtkxarch_int index)
{
    m_list.replace(index, qvariant_cast<T>(data));
};

template <typename T> inline void dtkContainerList<T>::resize(dtkxarch_int size)
{
    m_list.reserve(size);
};

template <typename T> inline bool dtkContainerList<T>::isEmpty(void) const
{
    return m_list.isEmpty();
};

template <typename T> inline bool dtkContainerList<T>::contains(const QVariant& data) const
{
    return m_list.contains(qvariant_cast<T>(data));
};

template <typename T> inline dtkxarch_int dtkContainerList<T>::count(void) const
{
    return m_list.count();
};

template <typename T> inline dtkxarch_int dtkContainerList<T>::indexOf(const QVariant& data, dtkxarch_int from) const
{
    return m_list.indexOf(qvariant_cast<T>(data), from);
};

template <typename T> inline QVariant dtkContainerList<T>::at(dtkxarch_int index) const
{
    return qVariantFromValue(m_list.at(index));
};

template <typename T> inline QVariant dtkContainerList<T>::first(void) const
{
    return qVariantFromValue(m_list.first());
};

template <typename T> inline QVariant dtkContainerList<T>::last(void) const
{
    return qVariantFromValue(m_list.last());
};

template <typename T> inline bool dtkContainerList<T>::operator != (const dtkContainerList<T>& other) const
{
    return (m_list != other.m_list);
};

template <typename T> inline bool dtkContainerList<T>::operator == (const dtkContainerList<T>& other) const
{
    return (m_list == other.m_list);
};

template <typename T> inline bool dtkContainerList<T>::isEqual(const dtkAbstractContainer& other) const
{
    if (other.type() == List) {
        if (const dtkContainerList<T> *other_v = dynamic_cast<const dtkContainerList<T> *>(&other)) {
            return (m_list == other_v->m_list);
        }
    }

    return false;
};

#endif
