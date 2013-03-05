/* dtkDistributedArrayItem.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 27 11:59:03 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

// /////////////////////////////////////////////////////////////////
// dtkDistributedArrayItem interface and implementation
// /////////////////////////////////////////////////////////////////
 
template <typename T> class dtkDistributedArrayItem
{
public:
    inline dtkDistributedArrayItem(dtkDistributedArray<T> *array, const qlonglong& index) : m_index(index), m_array(array) {;}
    inline dtkDistributedArrayItem(const dtkDistributedArrayItem<T>& other) : m_index(other.m_index), m_array(other.m_array) {;}

public:
    inline ~dtkDistributedArrayItem(void) { m_index = -1; m_array = 0; }

public:
    inline dtkDistributedArrayItem& operator = (const dtkDistributedArrayItem<T>& other) { m_index = other.m_index; m_array = other.m_array; }

public:
    inline dtkDistributedArrayItem& operator = (const T& value) { m_array->set(m_index, value); return *this; }

    inline dtkDistributedArrayItem& operator += (const T& value) { m_array->set(m_index, m_array->at(m_index) + value); return *this; }
    inline dtkDistributedArrayItem& operator -= (const T& value) { m_array->set(m_index, m_array->at(m_index) - value); return *this; }

    inline dtkDistributedArrayItem& operator *= (const T& value) { m_array->set(m_index, m_array->at(m_index) * value); return *this; }
    inline dtkDistributedArrayItem& operator /= (const T& value) { m_array->set(m_index, m_array->at(m_index) / value); return *this; }

private:
    dtkDistributedArrayItem& operator ++ (void) { return *this; }
    dtkDistributedArrayItem& operator -- (void) { return *this; }
    dtkDistributedArrayItem& operator ++ (int) { return *this; }
    dtkDistributedArrayItem& operator -- (int) { return *this; }

public:
    inline T value(void) const { return m_array->at(m_index); }

private:
    qlonglong m_index;

    dtkDistributedArray<T> *m_array;    
};
