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
// 
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedArrayItem
{
public:
    inline dtkDistributedArrayItem(void);
    inline dtkDistributedArrayItem(const dtkDistributedArrayItem<T>& other);

public:
    inline ~dtkDistributedArrayItem(void);

public:
    dtkDistributedArrayItem& operator = (const dtkDistributedArrayItem<T>& other);

public:
    inline dtkDistributedArrayItem& operator = (const T& value);

public:
    inline dtkDistributedArrayItem& operator ++ (void);
    inline dtkDistributedArrayItem& operator -- (void);

    inline dtkDistributedArrayItem& operator += (const T& value);
    inline dtkDistributedArrayItem& operator -= (const T& value);
    inline dtkDistributedArrayItem& operator *= (const T& value);
    inline dtkDistributedArrayItem& operator /= (const T& value);

public:
    inline T value(void) const;

private:
    friend class dtkDistributedArray<T>;

    inline dtkDistributedArrayItem(dtkDistributedArray<T> *array, const qlonglong& index);

private:
    qlonglong m_index;

    dtkDistributedArray<T> *m_array;
};

// /////////////////////////////////////////////////////////////////

template <typename T> dtkDistributedArrayItem<T>::dtkDistributedArrayItem(void) : m_index(-1), m_array(0)
{

}

template <typename T> dtkDistributedArrayItem<T>::dtkDistributedArrayItem(const dtkDistributedArrayItem& other) : m_index(other.m_index), m_array(other.m_array)
{

}

template <typename T> dtkDistributedArrayItem<T>::dtkDistributedArrayItem(dtkDistributedArray<T> *array, const qlonglong& index) : m_index(index), m_array(array)
{

}

template <typename T> dtkDistributedArrayItem<T>::~dtkDistributedArrayItem(void)
{
    m_index = -1;
    m_array = NULL;
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator = (const dtkDistributedArrayItem<T>& other)
{
    m_index = other.m_index;
    m_array = other.m_array;

    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator = (const T& value)
{
    m_array.set(m_index, value);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator ++ (void)
{
    m_array->set(m_index, m_array->at(m_index)++);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator -- (void)
{
    m_array->set(m_index, m_array->at(m_index)--);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator += (const T& value)
{
    m_array->set(m_index, m_array->at(m_index) + value);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator -= (const T& value)
{
    m_array->set(m_index, m_array->at(m_index) - value);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator *= (const T& value)
{
    m_array->set(m_index, m_array->at(m_index) * value);
    return (*this);
}

template <typename T> dtkDistributedArrayItem<T>& dtkDistributedArrayItem<T>::operator /= (const T& value)
{
    m_array->set(m_index, m_array->at(m_index) / value);
    return (*this);
}

template <typename T> T dtkDistributedArrayItem<T>::value(void) const
{
    return m_array->at(m_index);
}
