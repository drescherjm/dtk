// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedArrayData
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArrayData
{
    qlonglong  buffer_id;
    qlonglong  buffer_size;
    T         *buffer;

public:
    dtkDistributedArrayData(void) : buffer_id(-1), buffer_size(0), buffer(0) {}

public:
    void setData(T *data, const qlonglong& size, const qlonglong& id) { buffer = data; buffer_size = size; buffer_id = id; }

          T *data(void)       { return buffer; }
    const T *data(void) const { return buffer; }

    qlonglong size(void) const { return buffer_size; }
    qlonglong   id(void) const { return   buffer_id; }

    void setValue(const qlonglong& index, const T& value)
    { 
        buffer[index] = value;
    }

    const T& value(const qlonglong& index) const { return buffer[index]; }
    
public:
    class iterator 
    {
        friend class const_iterator;
        T *it;

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef qlonglong difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T& reference;

    public:
        iterator(void) : it(0) {}
        iterator(T *t) : it(t) {}

    public:
        T& operator *  (void) const { return *it; }
        T *operator -> (void) const { return  it; }
        T& operator [] (qlonglong j) const { return *(it + j); }
        bool operator == (const iterator &o) const { return it == o.it; }
        bool operator != (const iterator &o) const { return it != o.it; }
        bool operator <  (const iterator &o) const { return it  < o.it; }
        bool operator >  (const iterator &o) const { return it  > o.it; }
        bool operator <= (const iterator &o) const { return it <= o.it; }
        bool operator >= (const iterator &o) const { return it >= o.it; }
        iterator& operator ++ (void) { ++it; return *this; }
        iterator  operator ++ (int)  { T *t = it; ++it; return t; }
        iterator& operator -- (void) { --it; return *this; }
        iterator  operator -- (int)  { T *t = it; it--; return t; }
        iterator& operator += (qlonglong j) { it += j; return *this; }
        iterator& operator -= (qlonglong j) { it -= j; return *this; }
        iterator  operator +  (qlonglong j) const { return iterator(it + j); }
        iterator  operator -  (qlonglong j) const { return iterator(it - j); }
        qlonglong operator -  (const iterator& o) const { return it - o.it; }
                  operator T *(void) const { return it; }
    };
    friend class iterator;

public:
    class const_iterator 
    {
        const T *it;

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef qlonglong difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T& eference;

    public:
        const_iterator(void) : it(0) {}
        const_iterator(const T *t) : it(t) {}
        explicit const_iterator(const iterator &o): it(o.it) {}

    public:
        const T& operator *  (void) const { return *it; }
        const T *operator -> (void) const { return  it; }
        const T& operator [] (qlonglong j) const { return *(it + j); }
        bool operator == (const const_iterator &o) const { return it == o.it; }
        bool operator != (const const_iterator &o) const { return it != o.it; }
        bool operator <  (const const_iterator &o) const { return it  < o.it; }
        bool operator >  (const const_iterator &o) const { return it  > o.it; }
        bool operator <= (const const_iterator &o) const { return it <= o.it; }
        bool operator >= (const const_iterator &o) const { return it >= o.it; }
        const_iterator& operator ++ (void) { ++it; return *this; }
        const_iterator  operator ++ (int)  { T *t = it; ++it; return t; }
        const_iterator& operator -- (void) { --it; return *this; }
        const_iterator  operator -- (int)  { T *t = it; it--; return t; }
        const_iterator& operator += (qlonglong j) { it += j; return *this; }
        const_iterator& operator -= (qlonglong j) { it -= j; return *this; }
        const_iterator  operator +  (qlonglong j) const { return const_iterator(it + j); }
        const_iterator  operator -  (qlonglong j) const { return const_iterator(it - j); }
        qlonglong operator -  (const const_iterator& o) const { return it - o.it; }
                  operator const T *(void) const { return it; }
    };
    friend class const_iterator;

public:
          iterator  begin(iterator = iterator())                   { return buffer; }
          iterator    end(iterator = iterator())                   { return buffer + buffer_size; }
    const_iterator  begin(const_iterator = const_iterator()) const { return buffer; }
    const_iterator    end(const_iterator = const_iterator()) const { return buffer + buffer_size; }
    const_iterator cbegin(const_iterator = const_iterator()) const { return buffer; }
    const_iterator   cend(const_iterator = const_iterator()) const { return buffer + buffer_size; }
};

// 
// dtkDistributedArrayData.h ends here
