/* dtkSmartPointer.h ---
 *
 * Author: John Stark
 * Copyright (C) 2011 - John Stark, Inria.
 * Created: Wed May 25 14:00:00 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 25 16:00:00 2011 (+0100)
 *           By: John Stark
 *     Update #: 1
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKSMARTPOINTER_H
#define DTKSMARTPOINTER_H

#include <QHash>

template< class T > class dtkSmartPointer {
public:
    typedef T ObjectType;
    dtkSmartPointer() : d(0) { }

    dtkSmartPointer( const dtkSmartPointer<T> &p) :
        d(p.d)
    { this->retain(); }

    template <typename TR>
    dtkSmartPointer( const dtkSmartPointer<TR> &p) :
        d(dynamic_cast<T*>( p.operator->() ) )
    { this->retain(); }

    dtkSmartPointer (T *p) :
        d(p)
    { this->retain(); }

    ~dtkSmartPointer ()
    {
        this->release();
    }

    T* operator->() const
    { return d; }

    operator T* () const
    { return d; }

    bool isNull() const
    { return d == 0; }

    template <typename TR>
    bool operator == ( TR r ) const
    { return (d == static_cast<const T*>(r) ); }

    template <typename TR>
    bool operator == ( const dtkSmartPointer< TR > &r ) const
    { return (d == static_cast<const T*>(r.constData()) ); }

    template <typename TR>
    bool operator != ( TR r ) const
    { return (d != static_cast<const T*>(r) ); }

    template <typename TR>
    bool operator != ( const dtkSmartPointer< TR > &r ) const
    { return (d != static_cast<const T*>(r.constData()) ); }

    bool operator==( const dtkSmartPointer &r ) const
        { return d == r.d; }
    bool operator!=( const dtkSmartPointer &r ) const
        { return d != r.d; }
    bool operator<( const dtkSmartPointer &r ) const
        { return d < r.d; }
    bool operator<=( const dtkSmartPointer &r ) const
        { return d <= r.d; }
    bool operator>( const dtkSmartPointer &r ) const
        { return d > r.d; }
    bool operator>=( const dtkSmartPointer &r ) const
        { return d >= r.d; }

    T* data()
    { return d; }

    const T* constData() const
    { return d; }

    T& operator*()
    { return *d; }

    const T& operator*() const
    { return *d; }

    dtkSmartPointer& operator=(const dtkSmartPointer &r)
    { return this->operator=(r.d); }

    template <typename TR>
    dtkSmartPointer& operator=(const dtkSmartPointer<TR> &r)
    { return this->operator=(dynamic_cast<T*>( r.operator->() )); }

    dtkSmartPointer& operator = (T *r)
    {
        if (d != r)
        {
            T *tmp = d; //avoid recursive unregisters by retaining temporarily
            d = r;
            this->retain();
            if ( tmp ) { tmp->release(); }
        }
        return *this;
    }

    void swap( dtkSmartPointer &other)
    {
        T *tmp = d;
        d = other.d;
        other.d = tmp;
    }

    dtkSmartPointer& takePointer(T *r)
    {
        if (d != r)
        {
            T *tmp = d; //avoid recursive unregisters by retaining temporarily
            d = r;
            if ( tmp ) { tmp->release(); }
        }
        return *this;
    }

    T* releasePointer()
    {
        T *tmp = d;
        d = 0;
        return tmp;
    }

private:
    T *d;

    void retain()
    {
        if(d) { d->retain(); }
    }

    void release()
    {
        if(d) { d->release(); }
    }
};

template <class T>
inline uint qHash(const dtkSmartPointer<T> &key) { return qHash(key.constData()); }

#endif // DTKSMARTPOINTER_H

