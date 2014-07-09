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

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArrayNavigator
{
public:
    dtkDistributedArrayNavigator(dtkDistributedArray<T> *array) : m_array(array), m_start_id(0), m_size(0) {}
    dtkDistributedArrayNavigator(dtkDistributedArray<T> *array, qlonglong start, qlonglong size) : m_array(array), m_start_id(start), m_size(size) {}

public:
    void setRange(qlonglong start, qlonglong size) { m_start_id = start; m_size = size; }

public:
    class iterator
    {
        dtkDistributedArrayNavigator<T> *nav;
        qlonglong g_id;

    public:
        iterator(dtkDistributedArrayNavigator<T> *n, qlonglong id) : nav(n), g_id(id) {}
        iterator(const iterator& o) : nav(o.nav), g_id(o.g_id) {}

    public:
        T operator * (void) const { return nav->m_array->at(g_id); }
        T operator [] (qlonglong j) const { return *(*this + j); }
        bool operator == (const iterator &o) const { return g_id == o.g_id; }
        bool operator != (const iterator &o) const { return g_id != o.g_id; }
        bool operator <  (const iterator &o) const { return g_id  < o.g_id; }
        bool operator >  (const iterator &o) const { return g_id  > o.g_id; }
        bool operator <= (const iterator &o) const { return g_id <= o.g_id; }
        bool operator >= (const iterator &o) const { return g_id >= o.g_id; }
        iterator& operator ++ (void) { ++g_id; return *this; }
        iterator  operator ++ (int)  { iterator it(*this); ++g_id; return it; }
        iterator& operator -- (void) { --g_id; return *this; }
        iterator  operator -- (int)  { iterator it(*this); --g_id; return it; }
        iterator& operator += (qlonglong j) { g_id += j; return *this; }
        iterator& operator -= (qlonglong j) { g_id -= j; return *this; }
        iterator  operator +  (qlonglong j) const { return iterator(*this + j); }
        iterator  operator -  (qlonglong j) const { return iterator(*this - j); }
        qlonglong operator -  (const iterator& o) const { return g_id - o.g_id; }
    };

public:
    iterator begin(void) const { return iterator(const_cast<dtkDistributedArrayNavigator<T>*>(this), m_start_id); }
    iterator   end(void) const { return iterator(const_cast<dtkDistributedArrayNavigator<T>*>(this), m_start_id + m_size); }

public:
    qlonglong size(void) const { return m_size; }

private:
    dtkDistributedArray<T> *m_array;
    qlonglong m_start_id;
    qlonglong m_size;
};

// 
// dtkDistributedArrayNavigator.h ends here
