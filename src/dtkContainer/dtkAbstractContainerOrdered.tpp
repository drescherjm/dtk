/* dtkAbstractContainerOrdered.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 16:20:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 11:38:10 2012 (+0200)
 *           By: tkloczko
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINERORDERED_TPP
#define DTKABSTRACTCONTAINERORDERED_TPP

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerOrdered implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkAbstractContainerOrdered<T>::dtkAbstractContainerOrdered(void) : dtkAbstractContainer<T>()
{

}

template <typename T> inline dtkAbstractContainerOrdered<T>::dtkAbstractContainerOrdered(const dtkAbstractContainerOrdered<T>& other) : dtkAbstractContainer<T>(other)
{

}

template <typename T> inline dtkAbstractContainerOrdered<T>::~dtkAbstractContainerOrdered(void)
{

}

template <typename T> inline dtkContainerType dtkAbstractContainerOrdered<T>::type(void) const
{
    return dtkContainerTypeOrdered;
}

template <typename T> inline void dtkAbstractContainerOrdered<T>::add(const T& value)
{
    this->append(value);
}

template <typename T> inline void dtkAbstractContainerOrdered<T>::add(const dtkAbstractContainer<T>& values)
{
    this->append(values);
}

#endif
