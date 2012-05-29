/* dtkAbstractContainer.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 14:32:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 23 17:59:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINER_TPP
#define DTKABSTRACTCONTAINER_TPP

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkAbstractContainer<T>::dtkAbstractContainer(void)
{

}

template <typename T> inline dtkAbstractContainer<T>::dtkAbstractContainer(const dtkAbstractContainer<T>& other)
{

}

template <typename T> inline dtkAbstractContainer<T>::~dtkAbstractContainer(void)
{

}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator = (const dtkAbstractContainer<T>& other)
{
    return *(other.clone());
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator << (const T& value)
{
    this->add(value);
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator << (const dtkAbstractContainer<T>& values)
{
    this->add(values);
}

template <typename T> inline bool dtkAbstractContainer<T>::operator == (const dtkAbstractContainer<T>& other) const
{
    return this->isEqual(other);
}

template <typename T> inline bool dtkAbstractContainer<T>::operator != (const dtkAbstractContainer<T>& other) const
{
    return !(this->isEqual(other));
}

template <typename T> dtkAbstractContainer<T> dtkAbstractContainer<T>::operator + (const dtkAbstractContainer<T>& other) const
{
    dtkAbstractContainer<T> *result = this->clone(this);
    *(result) += other;

    return *result;
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator += (const dtkAbstractContainer<T>& other)
{
    this->add(other);

    return (*this);
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator += (const T& value)
{
    this->add(value);

    return (*this);
}

template <class T> QDebug operator<<(QDebug& dbg, const dtkAbstractContainer<T>& container)
{
    dbg.nospace() << container.identifier();

    return dbg.space();
}

template <class T> QDebug operator<<(QDebug& dbg, const dtkAbstractContainer<T> *container)
{
    dbg.nospace() << container->identifier();

    return dbg.space();
}

#endif
