/* dtkComposerVariant.tpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:56:15 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 12:56:38 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#ifndef DTKVARIANT_TPP
#define DTKVARIANT_TPP

#include "dtkComposerVariantHandler.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerVariant specific implementation declarations
// /////////////////////////////////////////////////////////////////

template<> QByteArray dtkComposerVariant::value(void) const;

// /////////////////////////////////////////////////////////////////
// dtkComposerVariant implementation
// /////////////////////////////////////////////////////////////////

inline QString dtkComposerVariant::identifier(void) const
{
    if (this->m_object)
        return this->m_object->identifier();

    if (this->m_matrix)
        return this->m_matrix->identifier();

    return this->typeName();
}

inline QString dtkComposerVariant::description(void) const
{
    if (this->m_object)
        return this->m_object->description();

    if (this->m_matrix)
        return this->m_matrix->description();

    return this->value<QString>();
}

inline void dtkComposerVariant::clear(void)
{
    this->QVariant::clear();
    this->m_object = NULL;
    this->m_data   = NULL;
    this->m_matrix = NULL;
}

template<typename T> bool dtkComposerVariant::canConvert(void) const
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isObjectPointer>::canConvert(*this);
};

inline bool dtkComposerVariant::isValid(void) const
{
    return this->QVariant::isValid();
}

inline bool dtkComposerVariant::isNull(void) const
{
    return this->QVariant::isNull();
}

inline bool dtkComposerVariant::isAbstractObject(void) const
{
    return this->m_object;
}

inline bool dtkComposerVariant::isAbstractData(void) const
{
    return this->m_data;
}

inline bool dtkComposerVariant::isMatrixReal(void) const
{
    return this->m_matrix;
}

inline dtkAbstractObject *dtkComposerVariant::toAbstractObject(void) const
{
    return this->m_object;
}

inline dtkAbstractData *dtkComposerVariant::toAbstractData(void) const
{
    return this->m_data;
}

inline dtkMatrixReal *dtkComposerVariant::toMatrixReal(void) const
{
    return this->m_matrix;
}

inline QByteArray dtkComposerVariant::toByteArray(void) const
{
    return this->value<QByteArray>();
}

template<typename T> void dtkComposerVariant::setValue(const T& value)
{
    dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isObjectPointer>::setValue(*this, value);
};

template<typename T> T dtkComposerVariant::value(void) const
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isObjectPointer>::value(*this);
};

inline void dtkComposerVariant::swap(dtkComposerVariant& other)
{
    qSwap(this->m_object, other.m_object);
    qSwap(this->m_data, other.m_data);
    qSwap(this->m_matrix, other.m_matrix);
    
    this->QVariant::swap(other);
}

#endif
