/* dtkMatrixSquared.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Mon Jul 12 15:58:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 12 16:05:19 2010 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKMATRIXSQUARED_TPP
#define DTKMATRIXSQUARED_TPP

#include "dtkMatrix.h"

// /////////////////////////////////////////////////////////////////
// Implementation of the template class dtkMatrixSquared's  methods
// /////////////////////////////////////////////////////////////////


template <class T> inline dtkMatrixSquared<T>::dtkMatrixSquared(const dtkMatrix<T> &mat,
                                                                unsigned irowStart,
                                                                unsigned icolStart,
                                                                unsigned irowEnd) : dtkMatrix<T>(mat,
                                                                                                 irowStart,
                                                                                                 icolStart,
                                                                                                 irowEnd,
                                                                                                 icolStart + irowEnd - irowStart)
{
}

template <class T> inline dtkMatrixSquared<T>::dtkMatrixSquared(const dtkMatrixSquared<T> &matSquared,
                                                                unsigned irowStart,
                                                                unsigned icolStart,
                                                                unsigned irowEnd) : dtkMatrix<T>(matSquared,
                                                                                                 irowStart,
                                                                                                 icolStart,
                                                                                                 irowEnd,
                                                                                                 icolStart + irowEnd - irowStart)
{
}

template <class T> inline void dtkMatrixSquared<T>::mapInto(const dtkMatrixSquared<T> &matSquared,
                                                            unsigned irowStart,
                                                            unsigned icolStart,
                                                            unsigned irowEnd)
{
    dtkMatrix<T>::mapInto(matSquared,
			  irowStart,
			  icolStart,
			  irowEnd,
			  icolStart + irowEnd - irowStart);
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator =(const dtkMatrixSquared<T> &matSquared)
{
    return static_cast<dtkMatrixSquared<T> &>(dtkMatrix<T>::operator=(matSquared));
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator +=(const dtkMatrixSquared<T> &matSquared)
{
    return static_cast<dtkMatrixSquared<T> &>(dtkMatrix<T>::operator+=(matSquared));
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator -=(const dtkMatrixSquared &matSquared)
{
    return static_cast<dtkMatrixSquared<T> &>(dtkMatrix<T>::operator-=(matSquared));
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator *=(const T &value)
{
    return static_cast<dtkMatrixSquared<T> &>(dtkMatrix<T>::operator*=(value));
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator *=(const dtkMatrixSquared<T> &matSquared)
{
    return (*this) = (*this)*matSquared;
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator /=(const T &value)
{
    T tTmp = dtkUnity<T>();
    tTmp /= value;
    return (*this) *= tTmp;
}

template <class T> inline dtkMatrixSquared<T> & dtkMatrixSquared<T>::operator /=(const dtkMatrixSquared<T> &matSquared)
{
    return (*this) = (*this)/matSquared;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator +(const dtkMatrixSquared<T> &matSquared) const
{
    return dtkMatrixSquared<T>(*this) += matSquared;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator -(const dtkMatrixSquared<T> &matSquared) const
{
    return dtkMatrixSquared<T>(*this) -= matSquared;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator -(void) const 
{
    T tTmp = dtkZero<T>();
    tTmp -= dtkUnity<T>();
    return (*this)*tTmp;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator *(const T &value) const
{
    return dtkMatrixSquared<T>(*this) *= value;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator *(const dtkMatrixSquared<T> &matSquared) const
{
    dtkMatrixSquared matSquaredResult(this->getRows());
    matSquaredResult.storeProduct(*this, matSquared);
    return matSquaredResult;
}

template <class T> dtkMatrixSquared<T> dtkMatrixSquared<T>::operator /(const dtkMatrixSquared<T> &matSquared) const
{
    return (*this)*inv(matSquared);
}

template <class T> void dtkMatrixSquared<T>::storeInverse(const dtkMatrixSquared<T> &matSquared)
{
    (*this) = matSquared;
    makeInverse();
}

template <class T> void dtkMatrixSquared<T>::makeUnity(void)
{
    unsigned crow(this->getRows()), ccol(this->getCols());

    for (unsigned irow = 0; irow < crow; ++irow) {
	for (unsigned icol = 0; icol < ccol; ++icol) {
	    if (irow == icol)
		(*this)[irow][icol] = dtkUnity<T>();
	    else
		(*this)[irow][icol] = dtkZero<T>();
        }
    }
}

template <class T> void dtkMatrixSquared<T>::makeAdjoint(void)
{
    // we need a copy of this
    dtkMatrixSquared matSquaredCopy(*this);
    // for easier access to crows
    unsigned crowCopy = matSquaredCopy.getRows();
    T elemTmp;
    // will eventually contain det(matSquaredCopy)
    T elemDet = dtkUnity<T>();

    // make this a unity matrix
    makeUnity();

    // start row reduction
    for (unsigned irow = 0; irow < crowCopy; ++irow) {
	// if element [irow][irow] is zero, add a row with non-zero
	// element at column irow
	if (matSquaredCopy[irow][irow] == dtkZero<T>()) {
	    for (unsigned irowTmp = irow; irowTmp < crowCopy; ++irowTmp) {
		if (matSquaredCopy[irowTmp][irow] != dtkZero<T>()) {
		    // has no effect on adj(matSquared)
		    matSquaredCopy.addRowToRow(irowTmp, irow);
		    // repeat action on this
		    this->addRowToRow(irowTmp, irow);
		    break;
                };
            };
        };

	elemTmp = matSquaredCopy[irow][irow];
        T tTmp = dtkUnity<T>();
        tTmp /= elemTmp;
	matSquaredCopy.multiplyRow(irow, tTmp);
	// repeat action on this
	multiplyRow(irow, tTmp);
	elemDet *= elemTmp;

	for (unsigned irowToAddTo = 0; irowToAddTo < crowCopy; ++irowToAddTo) {
	    if (irowToAddTo != irow) {
		elemTmp = -matSquaredCopy[irowToAddTo][irow];
		matSquaredCopy.addRowToRow(irow, irowToAddTo, elemTmp);
		// repeat action on this
		addRowToRow(irow, irowToAddTo, elemTmp);
            };
        };
    };

    // this now contains its adjoint
    (*this) *= elemDet;
}

template <class T> void dtkMatrixSquared<T>::storeAdjoint(const dtkMatrixSquared<T> &matSquared)
{
    (*this) = matSquared;
    makeAdjoint();
}

template <class T> void dtkMatrixSquared<T>::makeInverse(void)
{
    // we need a copy of this
    dtkMatrixSquared matSquaredCopy(*this);
    // for easier access to crows
    unsigned crowCopy = matSquaredCopy.getRows();
    T elemTmp;

    // make this a unity matrix
    makeUnity();

    // start row reduction
    for (unsigned irow = 0; irow < crowCopy; ++irow) {
	// if element [irow][irow] is zero, add a row with non-zero
	// element at column irow
	if (matSquaredCopy[irow][irow] == dtkZero<T>()) {
	    for (unsigned irowTmp = irow; irowTmp < crowCopy; ++irowTmp) {
		// has no effect on inv(matSquared)
		if (matSquaredCopy[irowTmp][irow] != dtkZero<T>()) {
		    matSquaredCopy.addRowToRow(irowTmp, irow);
		    // repeat action on this
		    this->addRowToRow(irowTmp, irow);
		    break;
                };
            };
        };

	elemTmp = matSquaredCopy[irow][irow];

        // NOTE: This used to work with g++ <= 3.2.
	// matSquaredCopy.multiplyRow(irow,
	//		     static_cast<const T &>(dtkUnity<T>()/elemTmp));
	// multiplyRow(irow, static_cast<const T &>(dtkUnity<T>()/elemTmp));
        T tTmp = dtkUnity<T>();
        tTmp /= elemTmp;
	matSquaredCopy.multiplyRow(irow, tTmp);
	multiplyRow(irow, tTmp);

	for (unsigned irowToAddTo = 0; irowToAddTo < crowCopy; ++irowToAddTo) {
	    if (irowToAddTo != irow) {
		elemTmp = -matSquaredCopy[irowToAddTo][irow];
		matSquaredCopy.addRowToRow(irow, irowToAddTo, elemTmp);
		// repeat action on this
		addRowToRow(irow, irowToAddTo, elemTmp);
            };
        };
    };

    // this now contains its inverse
}

template <class T> inline dtkMatrixSquared<T> operator *(const T &value,
                                                         const dtkMatrixSquared<T> &matSquared)
{
    return matSquared*value;
}

template <class T> dtkMatrixSquared<T> dtkTranspose(const dtkMatrixSquared<T> &matSquared)
{
    dtkMatrixSquared<T> matSquaredResult(matSquared.getRows());
    matSquaredResult.storeTranspose(matSquared);
    return matSquaredResult;
}

template <class T> dtkMatrixSquared<T> dtkAdjoint(const dtkMatrixSquared<T> &matSquared)
{
    dtkMatrixSquared<T> matSquaredResult(matSquared);      
    matSquaredResult.makeAdjoint();
    return matSquaredResult;
}

template <class T> dtkMatrixSquared<T> dtkInverse(const dtkMatrixSquared<T> &matSquared)
{
    dtkMatrixSquared<T> matSquaredResult(matSquared);
    matSquaredResult.makeInverse();
    return matSquaredResult;
}

template <class T> T dtkDeterminant(const dtkMatrixSquared<T> &matSquared)
{
    // a copy of the input matrix
    dtkMatrixSquared<T> matSquaredCopy(matSquared);
    unsigned crowCopy = matSquaredCopy.getRows();

    // start row reduction
    T elemTmp;
    // will eventually contain det(matSquaredCopy)
    T elemDet = dtkUnity<T>();

    for (unsigned irow = 0; irow < crowCopy; ++irow) {
	// if element [irow][irow] is zero, add a row with non-zero
	// element at column irow
	if (matSquaredCopy[irow][irow] == dtkZero<T>()) {
	    for (unsigned irowTmp = irow; irowTmp < crowCopy; ++irowTmp) {
		// has no effect on inv(matSquared)
		if (matSquaredCopy[irowTmp][irow] != dtkZero<T>()) {
		    matSquaredCopy.addRowToRow(irowTmp, irow);
		    break;
                };
            };
        };

	elemTmp =  matSquaredCopy[irow][irow];
	elemDet *= elemTmp;

	if (elemDet == dtkZero<T>()) {
	    // once elemDet is zero it will stay zero
	    return elemDet;
        }

	matSquaredCopy.multiplyRow(irow, dtkUnity<T>()/elemTmp);

	for (unsigned irowToAddTo = 0; irowToAddTo < crowCopy; ++irowToAddTo) {
	    if (irowToAddTo != irow) {
		matSquaredCopy.addRowToRow(irow,
                                           irowToAddTo,
                                           -matSquaredCopy[irowToAddTo][irow]);
            };
        };
    };

    return elemDet;
}

template <class T> T dtkTrace(const dtkMatrixSquared<T> &matSquared)
{
    T elemTmp = dtkZero<T>();

    for (unsigned c = 0; c < matSquared.getCols(); c++)
	elemTmp += matSquared[c][c];

    return elemTmp;
}

#endif
