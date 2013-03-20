/* dtkComposerVariantHandler.tpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:58:27 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 13:07:11 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Change Log:
 * 
 */

#ifndef DTKVARIANTHANDLER_TPP
#define DTKVARIANTHANDLER_TPP

#include "dtkComposerVariantHandler.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerVariantHandler implementation
// /////////////////////////////////////////////////////////////////

template<typename T, bool U> bool dtkComposerVariantHandler<T,U>::canConvert(const dtkComposerVariant& variant)
{
    return variant.QVariant::canConvert<T>();
}

template<typename T, bool U> bool dtkComposerVariantHandler<T,U>::canConvertToObject(const dtkComposerVariant& variant)
{
    return false; // end of cascading
}

template<typename T, bool U> bool dtkComposerVariantHandler<T,U>::canConvertToData(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isMatrixRealPointer>::canConvertToMatrixReal(variant); // cascading calls
}

template<typename T, bool U> bool dtkComposerVariantHandler<T,U>::canConvertToMatrixReal(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractObjectPointer>::canConvertToObject(variant); // cascading calls
}

template<typename T, bool U> void dtkComposerVariantHandler<T,U>::setValue(dtkComposerVariant& variant, const T& value)
{
    variant.QVariant::setValue(value);
    variant.m_object = NULL;
    variant.m_data   = NULL;
    variant.m_matrix = NULL;
}

template<typename T, bool U> void dtkComposerVariantHandler<T,U>::setObject(dtkComposerVariant& variant, const T& value)
{
    variant.m_object = NULL;
}

template<typename T, bool U> void dtkComposerVariantHandler<T,U>::setData(dtkComposerVariant& variant, const T& value)
{
    variant.m_data = NULL;
}

template<typename T, bool U> void dtkComposerVariantHandler<T,U>::setMatrixReal(dtkComposerVariant& variant, const T& value)
{
    variant.m_matrix = NULL;
}

template<typename T, bool U> T dtkComposerVariantHandler<T,U>::value(const dtkComposerVariant& variant)
{
    return variant.QVariant::value<T>();
}

template<typename T, bool U> T dtkComposerVariantHandler<T,U>::objectValue(const dtkComposerVariant& variant)
{
    return NULL; // end of the cascading calls
}

template<typename T, bool U> T dtkComposerVariantHandler<T,U>::dataValue(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isMatrixRealPointer>::matrixRealValue(variant); // cascading calls
}

template<typename T, bool U> T dtkComposerVariantHandler<T,U>::matrixRealValue(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractObjectPointer>::objectValue(variant); // cascading calls
}

// /////////////////////////////////////////////////////////////////
// dtkComposerVariantHandler specialized implementation
// /////////////////////////////////////////////////////////////////

template<typename T> bool dtkComposerVariantHandler<T, true>::canConvert(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractDataPointer>::canConvertToData(variant); // cascading calls
}

template<typename T> bool dtkComposerVariantHandler<T, true>::canConvertToObject(const dtkComposerVariant& variant)
{
    return (qobject_cast<T>(variant.m_object) != NULL);
}

template<typename T> bool dtkComposerVariantHandler<T, true>::canConvertToData(const dtkComposerVariant& variant)
{
    return (qobject_cast<T>(variant.m_data) != NULL);
}

template<typename T> bool dtkComposerVariantHandler<T, true>::canConvertToMatrixReal(const dtkComposerVariant& variant)
{
    return (dynamic_cast<T>(variant.m_matrix) != NULL);
}

template<typename T> void dtkComposerVariantHandler<T, true>::setValue(dtkComposerVariant& variant, const T& value)
{
    dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractObjectPointer>::setObject(variant, value);
    dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isMatrixRealPointer>::setMatrixReal(variant, value);
}

template<typename T> void dtkComposerVariantHandler<T, true>::setObject(dtkComposerVariant& variant, const T& value)
{
    variant.m_object = value;
    variant.QVariant::setValue(variant.m_object);

    dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractDataPointer>::setData(variant, value);
}

template<typename T> void dtkComposerVariantHandler<T, true>::setData(dtkComposerVariant& variant, const T& value)
{
    variant.m_data = value;
    variant.QVariant::setValue(variant.m_data);
}

template<typename T> void dtkComposerVariantHandler<T, true>::setMatrixReal(dtkComposerVariant& variant, const T& value)
{
    variant.m_matrix = value;
    variant.QVariant::setValue(variant.m_matrix);
}

template<typename T> T dtkComposerVariantHandler<T, true>::objectValue(const dtkComposerVariant& variant)
{
    return qobject_cast<T>(variant.m_object);
}

template<typename T> T dtkComposerVariantHandler<T, true>::dataValue(const dtkComposerVariant& variant)
{
    return qobject_cast<T>(variant.m_data);
}

template<typename T> T dtkComposerVariantHandler<T, true>::matrixRealValue(const dtkComposerVariant& variant)
{
    return dynamic_cast<T>(variant.m_matrix);
}

template<typename T> T dtkComposerVariantHandler<T, true>::value(const dtkComposerVariant& variant)
{
    return dtkComposerVariantHandler<T, dtkComposerTypeInfo<T>::isAbstractDataPointer>::dataValue(variant); // cascading calls...
}

// /////////////////////////////////////////////////////////////////
// Full specializations
// /////////////////////////////////////////////////////////////////

template<> inline void dtkComposerVariantHandler<dtkAbstractObject*, true>::setObject(dtkComposerVariant& variant, dtkAbstractObject*const& value)
{
    variant.m_object = value;
    variant.QVariant::setValue(variant.m_object);
    variant.m_data = qobject_cast<dtkAbstractData*>(variant.m_object);
}

template<> inline dtkAbstractObject *dtkComposerVariantHandler<dtkAbstractObject*, true>::value(const dtkComposerVariant& variant)
{
    return variant.m_object;
}

template<> inline dtkAbstractData *dtkComposerVariantHandler<dtkAbstractData*, true>::value(const dtkComposerVariant& variant)
{
    return variant.m_data;
}

template<> inline dtkMatrix<double> *dtkComposerVariantHandler<dtkMatrix<double>*, true>::value(const dtkComposerVariant& variant)
{
    return variant.m_matrix;
}

#endif
