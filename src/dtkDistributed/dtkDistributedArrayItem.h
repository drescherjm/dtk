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

#include "dtkDistributedItem.h"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////
 
template <typename T> class dtkDistributedArrayItem : public dtkDistributedContainerItem<T>
{
public:
    inline dtkDistributedArrayItem(dtkDistributedArray<T> *array, const qlonglong& index) : m_index(index), m_array(array) {;}

    inline ~dtkDistributedArrayItem(void) { m_index = -1; m_array = 0; }

public:
    inline void assign(const T& value) { m_array->set(m_index, value); }

    inline void increment(const T& value) { m_array->set(m_index, m_array->at(m_index) + value); }
    inline void decrement(const T& value) { m_array->set(m_index, m_array->at(m_index) - value); }

    inline void multiply(const T& value) { m_array->set(m_index, m_array->at(m_index) * value); }
    inline void   divide(const T& value) { m_array->set(m_index, m_array->at(m_index) / value); }

public:
    inline T value(void) const { return m_array->at(m_index); }

public:
    qlonglong m_index;

    dtkDistributedArray<T> *m_array;    
};
