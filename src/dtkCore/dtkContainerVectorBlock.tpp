/* dtkContainerVectorBlock.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 18:06:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 11:06:19 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 119
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTORBLOCK_TPP
#define DTKCONTAINERVECTORBLOCK_TPP

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorBlock implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkContainerVectorBlock<T>::dtkContainerVectorBlock(dtkAbstractData *parent) : dtkContainerVector<T>(parent)
{
    m_block_number = 0;
    m_block_size = 0;
};
     
template <typename T> dtkContainerVectorBlock<T>::dtkContainerVectorBlock(dtkxarch_int block_number, dtkxarch_int block_size, dtkAbstractData *parent) : dtkContainerVector<T>(parent), m_block_number(block_number), m_block_size(block_size)
{
    m_vector = QVector<T>(m_block_size * m_block_number);
    m_component_names = QStringList(m_block_size);
};

template <typename T> dtkContainerVectorBlock<T>::dtkContainerVectorBlock(const QVector<T>& vector, dtkxarch_int block_size, dtkAbstractData *parent) : dtkContainerVector(vector, parent), m_block_size(block_size)
{
    m_block_number = vector.count() / m_block_size;
    m_component_names = QStringList(m_block_size);
};

template <typename T> dtkContainerVectorBlock<T>::dtkContainerVectorBlock(const dtkContainerVectorBlock& other) : dtkContainerVector(other), m_block_number(other.m_block_number), m_block_size(other.m_block_size), m_component_names(other.m_component_names)
{

};

template <typename T> dtkContainerVectorBlock<T>::~dtkContainerVectorBlock(void)
{

};

template <typename T> dtkContainerVectorBlock<T>& dtkContainerVectorBlock<T>::operator = (const dtkContainerVectorBlock<T>& other)
{
    dtkContainerVector::operator=(other);

    m_block_number = other.m_block_number;
    m_block_size   = other.block_size;

    m_component_names = other.m_component_names;
    
    return *this;
};

template <typename T> dtkContainerVectorBlock<T> *dtkContainerVectorBlock<T>::clone(void) const
{
    return new dtkContainerVectorBlock<T>(*this);
};

template <typename T> dtkAbstractContainer::Type dtkContainerVectorBlock<T>::type(void) const
{
    return dtkAbstractContainer::VectorBlock;
};

template <typename T> inline void dtkContainerVector<T>::setVector(const QVector<T>& vector, dtkxarch_int block_size)
{
    m_vector = vector;
    m_block_size = block_size;
    m_block_number = vector.count() / block_size;
    m_component_names = QStringList(m_block_size);
};

template <typename T> inline void dtkContainerVector<T>::setVector(const QVector<T>& vector)
{
    m_vector = vector;
};

template <typename T> inline void dtkContainerVectorBlock<T>::clear(void)
{
    m_vector.clear();
    m_block_number = 0;
    m_block_size = 0;
    m_component_names.clear();
};

template <typename T> inline bool dtkContainerVectorBlock<T>::operator != (const dtkContainerVectorBlock<T>& other) const
{
    return ((m_vector != other.m_vector) || (m_block_size != other.m_block_size));
};

template <typename T> inline bool dtkContainerVectorBlock<T>::operator == (const dtkContainerVectorBlock<T>& other) const
{
    return ((m_vector == other.m_vector) && (m_block_size == other.m_block_size));
};

template <typename T> inline bool dtkContainerVectorBlock<T>::isEqual(const dtkAbstractContainer& other) const
{
    if (other.type() == Vector) {
        if (const dtkContainerVectorBlock<T> *other_v = dynamic_cast<const dtkContainerVectorBlock<T> *>(&other)) {
            return ((m_vector == other_v->m_vector) && (m_block_size == other.m_block_size));
        }
    }

    return false;
};

template <typename T> inline void dtkContainerVectorBlock<T>::setSize(dtkxarch_int block_number, dtkxarch_int block_size)
{
    m_block_number = block_number;
    m_block_size   = block_size;
};

template <typename T> void dtkContainerVectorBlock<T>::resize(dtkxarch_int block_number)
{
    if (block_number > m_block_number)
        m_vector.reserve(block_number * m_block_size);
    else
        m_vector.resize(block_number * m_block_size);

    m_block_number = block_number;
};

template <typename T> inline void dtkContainerVectorBlock<T>::append(const QVector<T>& block)
{
    m_vector << block;
};

template <typename T> inline void dtkContainerVectorBlock<T>::append(const dtkVector<T>& block)
{
    for(int i = 0; i < block.getRows(); ++i)
        m_vector << block[i];
};

template <typename T> inline void dtkContainerVectorBlock<T>::prepend(const QVector<T>& block)
{
    for(int i = 0; i < block.count(); ++i)
        m_vector.prepend(block.at(i));
};

template <typename T> inline void dtkContainerVectorBlock<T>::prepend(const dtkVector<T>& block)
{
    for(int i = 0; i < block.getRows(); ++i)
        m_vector.prepend(block[i]);
};

template <typename T> inline void dtkContainerVectorBlock<T>::remove(dtkxarch_int block_index)
{
    m_vector.remove(block_index*m_block_size, m_block_size);
};

template <typename T> inline void dtkContainerVectorBlock<T>::removeFirst(void)
{
    m_vector.remove(0, m_block_size);
};

template <typename T> inline void dtkContainerVectorBlock<T>::removeLast(void)
{
    m_vector.remove((m_block_number-1)*m_block_size, m_block_size);
};

template <typename T> inline void dtkContainerVectorBlock<T>::insert(dtkxarch_int block_index, const QVector<T>& block)
{
    dtkxarch_int begin = block_index * m_block_size;
    for(int i = 0; i < block.count(); ++i)
        m_vector.insert(begin + i, block.at(i));
};

template <typename T> inline void dtkContainerVectorBlock<T>::insert(dtkxarch_int block_index, const dtkVector<T>& block)
{
    dtkxarch_int begin = block_index * m_block_size;
    for(int i = 0; i < block.getRows(); ++i)
        m_vector.insert(begin + i, block[i]);
};

template <typename T> inline void dtkContainerVectorBlock<T>::replace(dtkxarch_int block_index, const QVector<T>& block)
{
    dtkxarch_int begin = block_index * m_block_size;
    for(int i = 0; i < block.count(); ++i)
        m_vector.replace(begin + i, block.at(i));
};

template <typename T> inline void dtkContainerVectorBlock<T>::replace(dtkxarch_int block_index, const dtkVector<T>& block)
{
    dtkxarch_int begin = block_index * m_block_size;
    for(int i = 0; i < block.getRows(); ++i)
        m_vector.replace(begin + i, block[i]);
};

template <typename T> inline dtkxarch_int dtkContainerVectorBlock<T>::numberOfBlocks(void) const
{
    return m_block_number;
};

template <typename T> inline dtkxarch_int dtkContainerVectorBlock<T>::blockSize(void) const
{
    return m_block_size;
};

template <typename T> inline QVector<T> dtkContainerVectorBlock<T>::blockAt(dtkxarch_int block_index)
{
    return m_vector.mid(block_index*m_block_size, m_block_size);
};

template <typename T> inline dtkVector<T> dtkContainerVectorBlock<T>::vectorAt(dtkxarch_int block_index)
{
    dtkVector vector(m_block_size);
    dtkxarch_int begin = block_index * m_block_size;
    for(int i = 0; i < m_block_size; ++i)
        vector[i] = m_vector.at(begin + i);

    return vector;
};

template <typename T> inline T *dtkContainerVectorBlock<T>::pointerAt(dtkxarch_int block_index)
{
    return &(m_vector.data()[block_index * m_block_size]);
};

template <typename T> inline void dtkContainerVectorBlock<T>::setComponentName(dtkxarch_int component_index, const QString& name)
{
    m_component_names[component_index] = name;
};

template <typename T> inline QString dtkContainerVectorBlock<T>::componentName(dtkxarch_int component_index) const
{
    return m_component_names.at(component_index);
};

template <typename T> inline void dtkContainerVectorBlock<T>::setComponentVector(dtkxarch_int component_index, const QVector<T>& vector)
{
    for(dtkxarch_int i = 0; i < m_block_number; ++i)
        m_vector[i*m_block_size + component_index] = vector.at(i);
};

template <typename T> inline QVector<T> dtkContainerVectorBlock<T>::componentVector(dtkxarch_int component_index) const
{
    QVector<T> vector(m_block_number);
    for(dtkxarch_int i = 0; i < m_block_number; ++i)
        vector[i] = m_vector.at(i*m_block_size + component_index);

    return vector;
};

template <typename T> inline void dtkContainerVectorBlock<T>::setComponentValue(dtkxarch_int block_index, dtkxarch_int component_index, const T& value)
{
    m_vector[block_index * m_block_size + component_index] = value;
};

template <typename T> inline T& dtkContainerVectorBlock<T>::componentValue(dtkxarch_int block_index, dtkxarch_int component_index)
{
    return m_vector[block_index * m_block_size + component_index];
};

template <typename T> inline const T& dtkContainerVectorBlock<T>::componentValue(dtkxarch_int block_index, dtkxarch_int component_index) const
{
    return m_vector[block_index * m_block_size + component_index];
};

template <typename T> void dtkContainerVectorBlock<T>::setComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices, const   QVector<T>& component_values)
{
    dtkxarch_int begin;

    for(dtkxarch_int i = 0; block_index < block_indices.count(); ++i) {
        begin = block_indices.at(i) * m_block_size;
        for(dtkxarch_int j = 0; component_indices.count(); ++j) {
            m_vector[begin + component_indices.at(j)] = component_values.at(j);
        }
    }            
};

template <typename T> void dtkContainerVectorBlock<T>::setBlockComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices, const dtkVector<T>& component_values)
{
    dtkxarch_int begin;

    for(dtkxarch_int i = 0; block_index < block_indices.count(); ++i) {
        begin = block_indices.at(i) * m_block_size;
        for(dtkxarch_int j = 0; component_indices.count(); ++j) {
            m_vector[begin + component_indices.at(j)] = component_values[j];
        }
    } 
};

template <typename T> inline QVector<T> dtkContainerVectorBlock<T>::componentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices) const
{
    QVector<T> vector(component_indices.count());
    dtkxarch_int begin;

    for(dtkxarch_int i = 0; block_index < block_indices.count(); ++i) {
        begin = block_indices.at(i) * m_block_size;
        for(dtkxarch_int j = 0; component_indices.count(); ++j) {
            vector[j] = m_vector.at(begin + component_indices.at(j));
        }
    }
};

template <typename T> inline dtkVector<T> dtkContainerVectorBlock<T>::vectorOfComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices) const
{
    dtkVector<T> vector(component_indices.count());
    dtkxarch_int begin;

    for(dtkxarch_int i = 0; block_index < block_indices.count(); ++i) {
        begin = block_indices.at(i) * m_block_size;
        for(dtkxarch_int j = 0; component_indices.count(); ++j) {
            vector[j] = m_vector.at(begin + component_indices.at(j));
        }
    }
};


#endif
