/* dtkAbstractContainerOrdered.tpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 16:20:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 30 16:47:55 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
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

template <typename T> dtkAbstractContainerOrdered<T>::dtkAbstractContainerOrdered(void) : dtkAbstractContainer<T>()
{

}

template <typename T> dtkAbstractContainerOrdered<T>::dtkAbstractContainerOrdered(const dtkAbstractContainerOrdered<T>& other) : dtkAbstractContainer<T>(other)
{

}

template <typename T> dtkAbstractContainerOrdered<T>::~dtkAbstractContainerOrdered(void)
{

}

template <typename T> dtkContainerType dtkAbstractContainerOrdered<T>::type(void) const
{
    return dtkContainerTypeOrdered;
}

template <typename T> void dtkAbstractContainerOrdered<T>::add(const T& value)
{
    this->append(value);
}

template <typename T> void dtkAbstractContainerOrdered<T>::add(const dtkAbstractContainer<T>& values)
{
    this->append(values);
}

#endif
