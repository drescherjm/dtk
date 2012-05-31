/* dtkContainerVector.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 12:30:17 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 30 15:41:32 2012 (+0200)
 *           By: tkloczko
 *     Update #: 250
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTOR_TPP
#define DTKCONTAINERVECTOR_TPP

// /////////////////////////////////////////////////////////////////
// dtkContainerVector implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(void) : dtkAbstractContainerOrdered<T>()
{
    
};

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(dtkxarch_int size) : dtkAbstractContainerOrdered<T>(), m_vector(size)
{

};

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(dtkxarch_int size, const T& value) : dtkAbstractContainerOrdered<T>(), m_vector(size, value)
{

};

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(const dtkContainerVector<T>& other) : dtkAbstractContainerOrdered<T>(other), m_vector(other.m_vector)
{

};

template <typename T> inline dtkContainerVector<T>::~dtkContainerVector(void)
{

};

template <typename T> inline QString dtkContainerVector<T>::identifier(void) const
{
    return QString("%1< %2 >")
        .arg("dtkContainerVector")
        .arg(typeid(T).name());
};

template <typename T> inline void dtkContainerVector<T>::clear(void)
{
    m_vector.clear();
};

template <typename T> inline void dtkContainerVector<T>::append(const T& value)
{
    m_vector.append(value);
};

template <typename T> inline void dtkContainerVector<T>::append(const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i)
        m_vector.append(array[i]);
};

template <typename T> inline void dtkContainerVector<T>::append(const dtkContainerVector<T>& values)
{
    m_vector << values.m_vector;
};

template <typename T> inline void dtkContainerVector<T>::prepend(const T& value)
{
    m_vector.prepend(value);
};

template <typename T> inline void dtkContainerVector<T>::prepend(const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i)
        m_vector.prepend(array[i]);
};

template <typename T> inline void dtkContainerVector<T>::prepend(const dtkContainerVector<T>& values)
{
    for(dtkxarch_int i = 0; i < values.count(); ++i)
        m_vector.prepend(values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::remove(const T& value)
{
    dtkxarch_int index = m_vector.indexOf(value);
    dtkxarch_int i;
    while (index >= 0) {
        m_vector.remove(index);
        i = index;
        index = m_vector.indexOf(value, i);
    }
};

template <typename T> void dtkContainerVector<T>::remove(const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i) {
        this->remove(array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::remove(const dtkContainerVector<T>& values)
{
    for(dtkxarch_int i = 0; i < values.count(); ++i)
        this->remove(values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::insert(dtkxarch_int index, const T& value)
{
    m_vector.insert(index, value);
};

template <typename T> inline void dtkContainerVector<T>::insert(dtkxarch_int from, const dtkAbstractContainer<T>& values)
{
    this->insert(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::insert(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values)
{
    m_vector.reserve(m_vector.count()+values.count());
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i) {
        m_vector.insert(i*step+from, array[i]);
    }
    m_vector.squeeze();
};

template <typename T> void dtkContainerVector<T>::insert(dtkxarch_int* indices, const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i) {
        m_vector.insert(indices[i], array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::insert(dtkxarch_int from, const dtkContainerVector<T>& values)
{
    this->insert(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::insert(dtkxarch_int from, dtkxarch_int step, const dtkContainerVector<T>& values)
{
    m_vector.reserve(m_vector.count()+values.count());
    for(dtkxarch_int i = 0; i < values.count(); ++i) {
        m_vector.insert(i*step+from, values.at(i));
    }
    m_vector.squeeze();
};

template <typename T> void dtkContainerVector<T>::insert(dtkxarch_int* indices, const dtkContainerVector<T>& values)
{
    for(dtkxarch_int i = 0; i < values.count(); ++i)
        m_vector.insert(indices[i], values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::replace(dtkxarch_int index, const T& value)
{
    m_vector.replace(index, value);
};

template <typename T> inline void dtkContainerVector<T>::replace(dtkxarch_int from, const dtkAbstractContainer<T>& values)
{
    this->replace(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::replace(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i) {
        m_vector.replace(i*step+from, array[i]);
    }
};

template <typename T> void dtkContainerVector<T>::replace(dtkxarch_int* indices, const dtkAbstractContainer<T>& values)
{
    dtkxarch_int size;
    const T *array = values.toArray(size);
    for(dtkxarch_int i = 0; i < size; ++i) {
        m_vector.replace(indices[i], array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::replace(dtkxarch_int from, const dtkContainerVector<T>& values)
{
    this->replace(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::replace(dtkxarch_int from, dtkxarch_int step, const dtkContainerVector<T>& values)
{
    for(dtkxarch_int i = 0; i < values.count(); ++i)
        m_vector.replace(i*step+from, values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::replace(dtkxarch_int* indices, const dtkContainerVector<T>& values)
{
    for(dtkxarch_int i = 0; i < values.count(); ++i)
        m_vector.replace(indices[i], values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::removeAt(dtkxarch_int index)
{
    m_vector.remove(index);
};

template <typename T> void dtkContainerVector<T>::removeAt(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step)
{
    if (step <= 0)
        return;

    dtkxarch_int size = (to - from) / step;
    dtkxarch_int index = from;
    while(size != 0) {
        this->removeAt(index);
        index += (step-1);
        --size;
    }
};

template <typename T> inline void dtkContainerVector<T>::reserve(dtkxarch_int value)
{
    m_vector.reserve(value);
};

template <typename T> inline void dtkContainerVector<T>::resize(dtkxarch_int size)
{
    m_vector.resize(size);
};

template <typename T> inline void dtkContainerVector<T>::squeeze(void)
{
    m_vector.squeeze();
};

template <typename T> inline bool dtkContainerVector<T>::isEmpty(void) const
{
    return m_vector.isEmpty();
};

template <typename T> inline bool dtkContainerVector<T>::contains(const T& value) const
{
    return m_vector.contains(value);
};

template <typename T> bool dtkContainerVector<T>::contains(const dtkAbstractContainer<T>& values) const
{
    bool result = true;
    dtkxarch_int size;
    const T *array = values.toArray(size);
    dtkxarch_int i = 0;
    while(result && (i < size)) {
        result = m_vector.contains(array[i++]);
    }
    
    return result;
};

template <typename T> inline bool dtkContainerVector<T>::contains(const dtkContainerVector<T>& values) const
{
    bool result = true;
    dtkxarch_int size = values.count();
    dtkxarch_int i = 0;
    while(result && (i < size)) {
        result = m_vector.contains(values.at(i++));
    }
    
    return result;
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::capacity(void) const
{
    return m_vector.capacity();
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::count(void) const
{
    return m_vector.count();
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::indexOf(const T& value, dtkxarch_int from)  const
{
    return m_vector.indexOf(value, from);
};

template <typename T> inline dtkxarch_int dtkContainerVector<T>::lastIndexOf(const T& value, dtkxarch_int from) const
{
    return m_vector.lastIndexOf(value, from);
};

template <typename T> inline dtkxarch_int *dtkContainerVector<T>::indicesOf(const T& value, dtkxarch_int from) const
{
    dtkContainerVector<dtkxarch_int> indices;
    dtkxarch_int index = m_vector.indexOf(value, from);
    while(index > 0 ) {
        indices << index;
        from = index+1;
        index = m_vector.indexOf(value, from);
    }

    return indices.array();
};

template <typename T> inline const T& dtkContainerVector<T>::at(dtkxarch_int index) const
{
    return m_vector.at(index);
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVector<T>::subContainer(const dtkAbstractContainerOrdered<dtkxarch_int>& indices) const
{
    dtkContainerVector<T> *result = new dtkContainerVector<T>();
    result->reserve(indices.count());
    for(dtkxarch_int i = 0; i < indices.count(); ++i)
        result->append(m_vector.at(indices.at(i)));

    return result;
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVector<T>::subContainer(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step) const
{
    dtkxarch_int size = (to - from) / step;
    dtkContainerVector<T> *result = new dtkContainerVector<T>();
    result->reserve(size);

    dtkxarch_int index = from;
    while(size != 0) {
        result->append(m_vector.at(index));
        index += step;
        --size;
    }

    return result;
};

template <typename T> inline const T *dtkContainerVector<T>::toArray(dtkxarch_int& count) const
{
    count = m_vector.count();
    
    return m_vector.data();
};

template <typename T> inline T *dtkContainerVector<T>::toArray(dtkxarch_int& count)
{
    count = m_vector.count();
    
    return m_vector.data();
};

template <typename T> inline T *dtkContainerVector<T>::array(void)
{
    return m_vector.data();
};

template <typename T> inline const T *dtkContainerVector<T>::array(void) const
{
    return m_vector.data();
};

template <typename T> inline const T *dtkContainerVector<T>::constArray(void) const
{
    return m_vector.constData();
};

template <typename T> inline const T& dtkContainerVector<T>::operator [] (dtkxarch_int index) const
{
    return m_vector.at(index);
};

template <typename T> inline T& dtkContainerVector<T>::operator [] (dtkxarch_int index)      
{
    return m_vector[index];
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVector<T>::operator = (const dtkContainerVector<T>& other)
{
    m_vector = other.m_vector;

    return (*this);
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVector<T>::clone(void) const
{
    return new dtkContainerVector<T>(*this);
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVector<T>::operator << (const T& value)
{
    m_vector << value;

    return (*this);
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVector<T>::operator << (const dtkContainerVector<T>& values)
{
    m_vector << values.m_vector;

    return (*this);
};

template <typename T> inline bool dtkContainerVector<T>::operator == (const dtkContainerVector<T>& other) const
{
    return (m_vector == other.m_vector);
};

template <typename T> inline bool dtkContainerVector<T>::operator != (const dtkContainerVector<T>& other) const
{
    return (m_vector != other.m_vector);
};

template <typename T> inline bool dtkContainerVector<T>::isEqual(const dtkAbstractContainer<T>& other) const
{
    if (this == &other)
        return true;

    if (m_vector.count() != other.count())
        return false;

    if (this->type() == other.type()) {

        dtkAbstractContainerOrdered<T> *other_o = const_cast<dtkAbstractContainerOrdered<T> *>(reinterpret_cast<const dtkAbstractContainerOrdered<T> *>(&other));

        bool is_equal = true;
        dtkxarch_int count = 0;
        while(is_equal && (count < m_vector.count())) {
            is_equal = (m_vector.at(count) == (*other_o)[count++]);
        }
        return is_equal;

    } else {

        return false;

    }

    return false;
};

template <typename T> inline dtkContainerVector<T> dtkContainerVector<T>::operator + (const dtkContainerVector<T>& other)
{
    return (m_vector + other.m_vector);
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVector<T>::operator += (const dtkContainerVector<T>& other)
{
    m_vector += other.m_vector;
    return (*this);
};

template <typename T> inline dtkContainerVector<T>& dtkContainerVector<T>::operator += (const T& value)
{
    m_vector += value;
    return (*this);
};

template <typename T> inline dtkContainerVector<T> dtkContainerVectorFromQVector(const QVector<T>& vector)
{
    dtkContainerVector<T> result;
    result.m_vector = vector;

    return result;
};

template <typename T> inline QVector<T> dtkContainerVectorToQVector(const dtkContainerVector<T>& vector)
{
    QVector<T> result(vector.m_vector);

    return result;
};

#endif
