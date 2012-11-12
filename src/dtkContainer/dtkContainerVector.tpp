/* dtkContainerVector.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 12:30:17 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 21 14:07:39 2012 (+0200)
 *           By: tkloczko
 *     Update #: 260
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

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(qlonglong size) : dtkAbstractContainerOrdered<T>(), m_vector(size)
{

};

template <typename T> inline dtkContainerVector<T>::dtkContainerVector(qlonglong size, const T& value) : dtkAbstractContainerOrdered<T>(), m_vector(size, value)
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
    return QString("dtkContainerVector<%1>").arg(typeid(T).name());
};

template <typename T> inline QString dtkContainerVector<T>::description(void) const
{
    QString string;

    string = "[ " ;

    // for (qlonglong i = 0; i < m_vector.count(); ++i)
    // {
    //     if (i > 0)
    //         string.append("; ");
    //     QString string2 = QString("%1").arg(m_vector.at(i));
    //     string += string2;
    // }

    string.append(" ]");

    return string;
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
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i)
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
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i)
        m_vector.prepend(array[i]);
};

template <typename T> inline void dtkContainerVector<T>::prepend(const dtkContainerVector<T>& values)
{
    for(qlonglong i = 0; i < values.count(); ++i)
        m_vector.prepend(values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::remove(const T& value)
{
    qlonglong index = m_vector.indexOf(value);
    qlonglong i;
    while (index >= 0) {
        m_vector.remove(index);
        i = index;
        index = m_vector.indexOf(value, i);
    }
};

template <typename T> void dtkContainerVector<T>::remove(const dtkAbstractContainer<T>& values)
{
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i) {
        this->remove(array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::remove(const dtkContainerVector<T>& values)
{
    for(qlonglong i = 0; i < values.count(); ++i)
        this->remove(values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::insert(qlonglong index, const T& value)
{
    m_vector.insert(index, value);
};

template <typename T> inline void dtkContainerVector<T>::insert(qlonglong from, const dtkAbstractContainer<T>& values)
{
    this->insert(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::insert(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values)
{
    m_vector.reserve(m_vector.count()+values.count());
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i) {
        m_vector.insert(i*step+from, array[i]);
    }
    m_vector.squeeze();
};

template <typename T> void dtkContainerVector<T>::insert(qlonglong* indices, const dtkAbstractContainer<T>& values)
{
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i) {
        m_vector.insert(indices[i], array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::insert(qlonglong from, const dtkContainerVector<T>& values)
{
    this->insert(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::insert(qlonglong from, qlonglong step, const dtkContainerVector<T>& values)
{
    m_vector.reserve(m_vector.count()+values.count());
    for(qlonglong i = 0; i < values.count(); ++i) {
        m_vector.insert(i*step+from, values.at(i));
    }
    m_vector.squeeze();
};

template <typename T> void dtkContainerVector<T>::insert(qlonglong* indices, const dtkContainerVector<T>& values)
{
    for(qlonglong i = 0; i < values.count(); ++i)
        m_vector.insert(indices[i], values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::replace(qlonglong index, const T& value)
{
    m_vector.replace(index, value);
};

template <typename T> inline void dtkContainerVector<T>::replace(qlonglong from, const dtkAbstractContainer<T>& values)
{
    this->replace(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::replace(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values)
{
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i) {
        m_vector.replace(i*step+from, array[i]);
    }
};

template <typename T> void dtkContainerVector<T>::replace(qlonglong* indices, const dtkAbstractContainer<T>& values)
{
    qlonglong size;
    const T *array = values.toArray(size);
    for(qlonglong i = 0; i < size; ++i) {
        m_vector.replace(indices[i], array[i]);
    }
};

template <typename T> inline void dtkContainerVector<T>::replace(qlonglong from, const dtkContainerVector<T>& values)
{
    this->replace(from, 1, values);
};

template <typename T> void dtkContainerVector<T>::replace(qlonglong from, qlonglong step, const dtkContainerVector<T>& values)
{
    for(qlonglong i = 0; i < values.count(); ++i)
        m_vector.replace(i*step+from, values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::replace(qlonglong* indices, const dtkContainerVector<T>& values)
{
    for(qlonglong i = 0; i < values.count(); ++i)
        m_vector.replace(indices[i], values.at(i));
};

template <typename T> inline void dtkContainerVector<T>::removeAt(qlonglong index)
{
    m_vector.remove(index);
};

template <typename T> void dtkContainerVector<T>::removeAt(qlonglong from, qlonglong to, qlonglong step)
{
    if (step <= 0)
        return;

    qlonglong size = (to - from) / step;
    qlonglong index = from;
    while(size != 0) {
        this->removeAt(index);
        index += (step-1);
        --size;
    }
};

template <typename T> inline void dtkContainerVector<T>::reserve(qlonglong value)
{
    m_vector.reserve(value);
};

template <typename T> inline void dtkContainerVector<T>::resize(qlonglong size)
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
    qlonglong size;
    const T *array = values.toArray(size);
    qlonglong i = 0;
    while(result && (i < size)) {
        result = m_vector.contains(array[i++]);
    }
    
    return result;
};

template <typename T> inline bool dtkContainerVector<T>::contains(const dtkContainerVector<T>& values) const
{
    bool result = true;
    qlonglong size = values.count();
    qlonglong i = 0;
    while(result && (i < size)) {
        result = m_vector.contains(values.at(i++));
    }
    
    return result;
};

template <typename T> inline qlonglong dtkContainerVector<T>::capacity(void) const
{
    return m_vector.capacity();
};

template <typename T> inline qlonglong dtkContainerVector<T>::count(void) const
{
    return m_vector.count();
};

template <typename T> inline qlonglong dtkContainerVector<T>::indexOf(const T& value, qlonglong from)  const
{
    return m_vector.indexOf(value, from);
};

template <typename T> inline qlonglong dtkContainerVector<T>::lastIndexOf(const T& value, qlonglong from) const
{
    return m_vector.lastIndexOf(value, from);
};

template <typename T> inline qlonglong *dtkContainerVector<T>::indicesOf(const T& value, qlonglong from) const
{
    dtkContainerVector<qlonglong> indices;
    qlonglong index = m_vector.indexOf(value, from);
    while(index > 0 ) {
        indices << index;
        from = index+1;
        index = m_vector.indexOf(value, from);
    }

    return indices.array();
};

template <typename T> inline const T& dtkContainerVector<T>::at(qlonglong index) const
{
    return m_vector.at(index);
};

template <typename T> inline const T& dtkContainerVector<T>::first(void) const
{
    return m_vector.first();
};


template <typename T> inline const T& dtkContainerVector<T>::last(void) const
{
    return m_vector.last();
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVector<T>::subContainer(const dtkAbstractContainerOrdered<qlonglong>& indices) const
{
    dtkContainerVector<T> *result = new dtkContainerVector<T>();
    result->reserve(indices.count());
    for(qlonglong i = 0; i < indices.count(); ++i)
        result->append(m_vector.at(indices.at(i)));

    return result;
};

template <typename T> inline dtkContainerVector<T> *dtkContainerVector<T>::subContainer(qlonglong from, qlonglong to, qlonglong step) const
{
    qlonglong size = (to - from) / step;
    dtkContainerVector<T> *result = new dtkContainerVector<T>();
    result->reserve(size);

    qlonglong index = from;
    while(size != 0) {
        result->append(m_vector.at(index));
        index += step;
        --size;
    }

    return result;
};

template <typename T> inline const T *dtkContainerVector<T>::toArray(qlonglong& count) const
{
    count = m_vector.count();
    
    return m_vector.data();
};

template <typename T> inline T *dtkContainerVector<T>::toArray(qlonglong& count)
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

template <typename T> inline const T& dtkContainerVector<T>::operator [] (qlonglong index) const
{
    return m_vector.at(index);
};

template <typename T> inline T& dtkContainerVector<T>::operator [] (qlonglong index)      
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
        qlonglong count = 0;
        while(is_equal && (count < m_vector.count())) {
            is_equal = (m_vector.at(count) == (*other_o)[count]);
            count++;
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
