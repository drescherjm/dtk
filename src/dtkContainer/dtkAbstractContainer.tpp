/* dtkAbstractContainer.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 14:32:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 22 16:20:00 2012 (+0200)
 *           By: tkloczko
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifnedf DTKABSTRACTCONTAINER_TPP
#define DTKABSTRACTCONTAINER_TPP

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkAbstractContainer::dtkAbstractContainer(void)
{

}

template <typename T> inline dtkAbstractContainer::dtkAbstractContainer(const dtkAbstractContainer<T>& other)
{

}

template <typename T> inline dtkAbstractContainer::~dtkAbstractContainer(void)
{

}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer::operator = (const dtkAbstractContainer<T>& other)
{
    return *(other.clone());
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer::operator << (const T& value)
{
    this->add(value);
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer::operator << (const dtkAbstractContainer<T>& values)
{
    this->add(values);
}

template <typename T> inline bool dtkAbstractContainer::operator == (const dtkAbstractContainer<T>& other)
{
    return this->isEqual(other);
}

template <typename T> inline bool dtkAbstractContainer::operator != (const dtkAbstractContainer<T>& other)
{
    return !(this->isEqual(other));
}

template <typename T> dtkAbstractContainer<T> dtkAbstractContainer::operator + (const dtkAbstractContainer<T>& other)
{
    dtkAbstractContainer<T> *result = this->clone(this);
    *(result) += other;

    return *result;
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer::operator += (const dtkAbstractContainer<T>& other)
{
    this->add(other);

    return (*this);
}

template <typename T> inline dtkAbstractContainer<T>& dtkAbstractContainer::operator += (const T& value)
{
    this->add(value);

    return (*this);
}

template <class T> QDebug operator<<(QDebug& dbg, const dtkAbstractContainer<T>& container)
{
    dbg.nospace() << this.identifier();

    return dbg.space();
}

template <class T> QDebug operator<<(QDebug& dbg, const dtkAbstractContainer<T> *container)
{
    dbg.nospace() << this->identifier();

    return dbg.space();
}

#endif
