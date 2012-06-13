/* dtkVector.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Mon Jul 12 16:04:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:38:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVECTOR_TPP
#define DTKVECTOR_TPP

#include <cmath>

#include "dtkMatrix.h"
#include "dtkMatrixSquared.h"

// /////////////////////////////////////////////////////////////////
// Implementation of the template class dtkVector's methods
// /////////////////////////////////////////////////////////////////

template <class T> inline dtkVector<T>::dtkVector(const dtkVector<T>& vec,
                                                  unsigned irowStart,
                                                  unsigned irowEnd) : dtkMatrix<T>(vec, irowStart, 0, irowEnd, 0)
{
}

template <class T> inline dtkVector<T>::dtkVector(const dtkMatrix<T>& mat,
                                                  unsigned irowStart,
                                                  unsigned icolStart,
                                                  unsigned irowEnd) : dtkMatrix<T>(mat, irowStart, icolStart, irowEnd, icolStart)
{
}

template <class T> inline void dtkVector<T>::mapInto(const dtkMatrix<T>& mat,
                                                     unsigned irowStart,
                                                     unsigned icol,
                                                     unsigned irowEnd)
{
    dtkMatrix<T>::mapInto(mat, irowStart, icol, irowEnd, icol);
}

template <class T> inline void dtkVector<T>::mapInto(const dtkVector& vec,
                                                     unsigned irowStart,
                                                     unsigned irowEnd)
{
    dtkMatrix<T>::mapInto(vec, irowStart, 0, irowEnd, 0);
}

template <class T> inline dtkVector<T>& dtkVector<T>::operator =(const dtkVector<T>& vec)
{
    return static_cast<dtkVector&>(dtkMatrix<T>::operator=(vec));
}

template <class T> inline dtkVector<T>& dtkVector<T>::operator +=(const dtkVector<T>& vec)
{
    return static_cast<dtkVector&>(dtkMatrix<T>::operator+=(vec));
}

template <class T> inline dtkVector<T>& dtkVector<T>::operator -=(const dtkVector<T>& vec)
{
    return static_cast<dtkVector&>(dtkMatrix<T>::operator-=(vec));
}

template <class T> inline dtkVector<T>& dtkVector<T>::operator *=(const T& value)
{
    return static_cast<dtkVector&>(dtkMatrix<T>::operator*=(value));
}

template <class T> inline dtkVector<T>& dtkVector<T>::operator /=(const T& value)
{
    T tTmp = dtkUnity<T>();
    tTmp /= value;
    return (*this) *= tTmp;
}

template <class T> inline void dtkVector<T>::storeAtRow(unsigned irowStart,
                                                        const dtkVector<T>& vec)
{
    dtkMatrix<T>::storeAtPosition(irowStart, 0, vec);
}

template <class T> dtkVector<T> dtkVector<T>::operator +(const dtkVector<T>& vec) const
{
    return dtkVector<T>(*this) += vec;
}

template <class T> dtkVector<T> dtkVector<T>::operator -(const dtkVector<T>& vec) const
{
    return dtkVector<T>(*this) -= vec;
}

template <class T> dtkVector<T> dtkVector<T>::operator -(void) const
{
    T tTmp = dtkZero<T>();
    tTmp -= dtkUnity<T>();
    return (*this)*tTmp;
}

 template <class T> dtkVector<T> dtkVector<T>::operator *(const T& value) const
{
    return dtkVector<T>(*this) *= value;
}

template <class T> T dtkVector<T>::operator *(const dtkVector<T>& vec) const
{
    T elemResult = dtkZero<T>();

    for (unsigned irow = 0; irow < (*this).getRows(); ++irow) 
	elemResult += (*this)[irow]*vec[irow];

    return elemResult;
}

template <class T> T dtkVector<T>::norm(void) const
{
    T elemResult = dtkZero<T>();

    elemResult = (*this)*(*this);

    return sqrt( elemResult );
}

template <class T> inline dtkVector<T> operator *(const T& value, const dtkVector<T>& vec)
{
    return vec*value;
}

template <class T> dtkVector<T> operator *(const dtkMatrix<T>& mat, const dtkVector<T>& vec)
{
    dtkVector<T> vecResult(mat.getRows());
    vecResult.storeProduct(mat, vec);
    return vecResult;
}

template <class T> dtkVector<T> operator *(const dtkMatrixSquared<T>& mat, const dtkVector<T>& vec)
{
    dtkVector<T> vecResult(mat.getRows());
    vecResult.storeProduct(mat, vec);
    return vecResult;
}

template <class T> inline T dtkNorm(const dtkVector<T>& vec)
{
    return vec.norm();
}

template <class T> inline dtkVector<T> dtkDirection(const dtkVector<T>& vec)
{
    return vec.unit();
}

#endif
