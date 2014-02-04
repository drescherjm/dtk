/* dtkAbstractContainer.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 14:32:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 30 17:02:14 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINER_TPP
#define DTKABSTRACTCONTAINER_TPP

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

template <> DTKCONTAINERSUPPORT_EXPORT QString dtkAbstractContainer<double>::description(void) const;

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkAbstractContainer<T>::dtkAbstractContainer(void)
{

}

template <typename T> dtkAbstractContainer<T>::dtkAbstractContainer(const dtkAbstractContainer<T>& other)
{

}

template <typename T> dtkAbstractContainer<T>::~dtkAbstractContainer(void)
{

}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator = (const dtkAbstractContainer<T>& other)
{
    return *(other.clone());
}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator << (const T& value)
{
    this->add(value);
}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator << (const dtkAbstractContainer<T>& values)
{
    this->add(values);
}

template <typename T> bool dtkAbstractContainer<T>::operator == (const dtkAbstractContainer<T>& other) const
{
    return this->isEqual(other);
}

template <typename T> bool dtkAbstractContainer<T>::operator != (const dtkAbstractContainer<T>& other) const
{
    return !(this->isEqual(other));
}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator + (const dtkAbstractContainer<T>& other) const
{
    dtkAbstractContainer<T> *result = this->clone(this);
    *(result) += other;

    return *result;
}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator += (const dtkAbstractContainer<T>& other)
{
    this->add(other);

    return (*this);
}

template <typename T> dtkAbstractContainer<T>& dtkAbstractContainer<T>::operator += (const T& value)
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
