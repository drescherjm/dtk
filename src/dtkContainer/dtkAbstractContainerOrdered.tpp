/* dtkAbstractContainerOrdered.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 16:20:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 22 16:24:27 2012 (+0200)
 *           By: tkloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINERORDERED_H
#define DTKABSTRACTCONTAINERORDERED_H

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerOrdered implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkAbstractContainerOrdered::dtkAbstractContainerOrdered(void) : dtkAbstractContainer()
{

}

template <typename T> inline dtkAbstractContainerOrdered::dtkAbstractContainerOrdered(const dtkAbstractContainer<T>& other) : dtkAbstractContainer(other)
{

}

template <typename T> inline dtkAbstractContainerOrdered::~dtkAbstractContainerOrdered(void)
{

}

template <typename T> inline dtkAbstractContainer::Type dtkAbstractContainerOrdered::type(void) const
{
    return dtkAbstractContainer::Ordered;
}

template <typename T> inline void dtkAbstractContainerOrdered::add(const T& value)
{
    this->append(value);
}

template <typename T> inline void dtkAbstractContainerOrdered::add(const dtkAbstractContainer<T>& values)
{
    this->append(values);
}

#endif
