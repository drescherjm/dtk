/* dtkMath.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jun  8 15:37:50 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  9 11:36:14 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 144
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKMATH_H
#define DTKMATH_H

#include "dtkMatrixSquared.h"
#include "dtkQuaternion.h"
#include "dtkVector3D.h"

#include "dtkMathExport.h"

DTKMATH_EXPORT
void dtkBubbleSort(unsigned int indices[], int size) ;

//! dtkMixedProduct(const dtkVector3D &v0, const dtkVector3D &v1, const dtkVector3D &v2)
/*! 
 * This function calculates the mixed product (also called triple scalar product)
 * formed by three dtkVector3D.
 */
template <class T>  T dtkMixedProduct(const dtkVector3D<T> &v0, 
                                      const dtkVector3D<T> &v1, 
                                      const dtkVector3D<T> &v2)
{
    dtkVector3D<T> v;
    v.storeOuterProduct(v1, v2);
    return (v0*v);
}

//! dtkMatSquaredFromEuler321(rotateAbout3, rotateAbout2, rotateAbout1)
/*!
 * This function returns a transformation matrix which transforms coordinates from
 * the reference axis system to coordinates in an axis system with
 * Euler angles: rotateAbout3, rotateAbout2, rotateAbout1 relative to that
 * reference axis system.
 *
 * rotation about axis 3 (yaw angle), axis 2 (pitch angle) axis 1
 * (roll angle)
*/
template <class T> dtkMatrixSquared<T> dtkMatSquaredFromEuler321Angles(T rotateAbout3,
                                                                   T rotateAbout2,
                                                                   T rotateAbout1)
{
    dtkMatrixSquared<T> mat(3U);

    T sin3 = sin(rotateAbout3);
    T sin2 = sin(rotateAbout2);
    T sin1 = sin(rotateAbout1);

    T cos3 = cos(rotateAbout3);
    T cos2 = cos(rotateAbout2);
    T cos1 = cos(rotateAbout1);

    mat[0][0] =  cos3*cos2;
    mat[0][1] =  sin3*cos2;
    mat[0][2] = -sin2;

    mat[1][0] = -sin3*cos1 + cos3*sin2*sin1;
    mat[1][1] =  cos3*cos1 + sin3*sin2*sin1;
    mat[1][2] =  cos2*sin1;

    mat[2][0] =  sin3*sin1 + cos3*sin2*cos1;
    mat[2][1] = -cos3*sin1 + sin3*sin2*cos1;
    mat[2][2] =  cos2*cos1;

    return mat;
}

//! dtkEuler321Angle3FromMatSquared(const dtkMatrixSquared<T> &mat)
/* 
 * Computation of the Euler yaw angle (rotation about Z-axis) from a transformation matrix.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle3FromMatSquared(const dtkMatrixSquared<T> &mat)
{
    return atan2(mat[0][1], mat[0][0]);
}

//! dtkEuler321Angle2FromMatSquared(const dtkMatrixSquared<T> &mat)
/* 
 * Computation of the Euler pitch angle (rotation angle about Y-axis) from a transformation matrix.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle2FromMatSquared(const dtkMatrixSquared<T> &mat)
{
    return asin(-mat[0][2]);
}

//! dtkEuler321Angle1FromMatSquared(const dtkMatrixSquared<T> &mat)
/* 
 * Computation of the Euler roll angle (rotation angle about X-axis) from a transformation matrix.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle1FromMatSquared(const dtkMatrixSquared<T> &mat)
{
    return atan2(mat[1][2], mat[2][2]);
}

//! dtkEuler321Angle3FromQuaternion(const dtkQuaternion<T> &qtn)
/* 
 * Computation of the Euler yaw angle (rotation angle about Z-axis) from a quaternion
 * that represents a rigid body's attitude.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle3FromQuaternion(const dtkQuaternion<T> &qtn)
{
    T qtn0 = qtn[0];
    T qtn1 = qtn[1];
    T qtn2 = qtn[2];
    T qtn3 = qtn[3];

    // NOTE: Speed tip from Jeffrey T Duncan: use the identity: 1 =
    // q0^2 + q1^2 + q2^2 + q3^2 which simplifies: q0^2 - q1^2 -
    // q2^2 + q3^2 down to: 2*(q0^2 + q3^2) - 1
    return atan2(2*(qtn0*qtn1 + qtn2*qtn3),
		 2*(qtn0*qtn0 + qtn3*qtn3) - 1);
}

//! dtkEuler321Angle2FromQuaternion(const dtkQuaternion<T> &qtn)
/* 
 * Computation of the Euler pitch angle (rotation angle about Y-axis) from a quaternion
 * that represents a rigid body's attitude.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle2FromQuaternion(const dtkQuaternion<T> &qtn)
{
    return asin(-2*(qtn[0]*qtn[2] - qtn[1]*qtn[3]));
}

//! dtkEuler321Angle1FromQuaternion(const dtkQuaternion<T> &qtn)
/* 
 * Computation of the Euler roll angle (rotation angle about X-axis) from a quaternion
 * that represents a rigid body's attitude.
 * WARNING!!! This function suffers from the ubiquitos singularities at 0, pi, 2*pi, etc.
 */
template <class T> T dtkEuler321Angle1FromQuaternion(const dtkQuaternion<T> &qtn)
{
    T qtn0 = qtn[0];
    T qtn1 = qtn[1];
    T qtn2 = qtn[2];
    T qtn3 = qtn[3];

    return atan2(2*(qtn1*qtn2 + qtn0*qtn3),
		 2*(qtn2*qtn2 + qtn3*qtn3) - 1);
}

//! dtkQuaternionFromEulerAxisAndAngle(const dtkVector3D<T> &dtkVecEulerAxis, const T &rotateEulerAngle)
/*! 
 * This function returns a quaternion representing a rigid body's 
 * attitude from its Euler axis and angle. 
 * NOTE: Argument vector dtkVecEulerAxis MUST be a unit vector.
 */
template <class T> dtkQuaternion<T> dtkQuaternionFromEulerAxisAndAngle(const dtkVector3D<T> &dtkVecEulerAxis,
                                                                       const T &rotateEulerAngle)
{
    return dtkQuaternion<T>(1, dtkVecEulerAxis, 0.5*rotateEulerAngle);
}

//! dtkEulerAxisFromQuaternion(const dtkQuaternion<T> &qtn)
/*!
 * This function returns Euler axis from a quaternion representing a rigid body's
 * attitude.
 */
template <class T> dtkVector3D<T> dtkEulerAxisFromQuaternion(const dtkQuaternion<T> &qtn)
{
    T sclrTmp = sqrt(1 - qtn[3]*qtn[3]);

    return dtkVector3D<T>(qtn[0]/sclrTmp,
			     qtn[1]/sclrTmp,
			     qtn[2]/sclrTmp);
}

//! dtkEulerAngleFromQuaternion(const dtkQuaternion<T> &qtn)
/*!
 * This function returns Euler angle from a quaternion representing a rigid body's
 * attitude.
 */
template <class T> T dtkEulerAngleFromQuaternion(const dtkQuaternion<T> &qtn)
{
    return 2*acos(qtn[3]);
}

//! dtkQuaternionFromEuler321Angles(T rotateAbout3, T rotateAbout2, T rotateAbout1)
/*! 
 * This function returns a quaternion representing a
 * rigid body's attitude. The quaternion elements correspond to the
 * Euler symmetric parameters of the body. The body's attitude must
 * be entered in Euler angle representation with rotation order
 * 3-2-1, i.e. first about Z-axis next about Y-axis and finally
 * about X-axis.
 */
template <class T> dtkQuaternion<T> dtkQuaternionFromEuler321Angles(T rotateAbout3,
                                                                    T rotateAbout2,
                                                                    T rotateAbout1)
{
    return dtkQuaternion<T>(1, dtkVector3D<T>(0, 0, 1), 0.5*rotateAbout3)
        * dtkQuaternion<T>(1, dtkVector3D<T>(0, 1, 0), 0.5*rotateAbout2)
        * dtkQuaternion<T>(1, dtkVector3D<T>(1, 0, 0), 0.5*rotateAbout1);
}

//! dtkMatSquaredFromQuaternion(const dtkQuaternion<T> &qtn)
/*! 
 * This function returns the transformation matrix corresponding to a
 * quaternion.
*/
template <class T> dtkMatrixSquared<T> dtkMatSquaredFromQuaternion(const dtkQuaternion<T> &qtn)
{
    dtkMatrixSquared<T> mat(3U);

    T qtn0 = qtn[0];
    T qtn1 = qtn[1];
    T qtn2 = qtn[2];
    T qtn3 = qtn[3];

    mat[0][0] = 1 - 2*(qtn1*qtn1 + qtn2*qtn2);
    mat[0][1] = 2*(qtn0*qtn1 + qtn2*qtn3);
    mat[0][2] = 2*(qtn0*qtn2 - qtn1*qtn3);

    mat[1][0] = 2*(qtn0*qtn1 - qtn2*qtn3);
    mat[1][1] = 1 - 2*(qtn0*qtn0 + qtn2*qtn2);
    mat[1][2] = 2*(qtn1*qtn2 + qtn0*qtn3);

    mat[2][0] = 2*(qtn0*qtn2 + qtn1*qtn3);
    mat[2][1] = 2*(qtn1*qtn2 - qtn0*qtn3);
    mat[2][2] = 1 - 2*(qtn0*qtn0 + qtn1*qtn1);

    return mat;
}

//! dtkQuaternionFromMatSquared(const dtkMatrixSquared<T> &mat)
/*! 
 * This function returns the quaternion corresponding to a
 * transformation matrix.
*/
template <class T> dtkQuaternion<T> dtkQuaternionFromMatSquared(const dtkMatrixSquared<T> &mat)
{
    T sclrTmp = dtkTrace(mat);

    dtkQuaternion<T> qtn;

    if(sclrTmp > 0) {
	sclrTmp = 0.5*sqrt(1 + sclrTmp);
	qtn[0] = 0.25*(mat[1][2] - mat[2][1])/sclrTmp;
	qtn[1] = 0.25*(mat[2][0] - mat[0][2])/sclrTmp;
	qtn[2] = 0.25*(mat[0][1] - mat[1][0])/sclrTmp;
	qtn[3] = sclrTmp;
    } else {
	// We could be in trouble, so we have to take
	// precautions. NOTE: Parts of this piece of code were taken
	// from the example in the article "Rotating Objects Using
	// Quaternions" in Game Developer Magazine written by Nick
	// Bobick, july 3, 1998, vol. 2, issue 26.
	int i = 0;
	if (mat[1][1] > mat[0][0]) i = 1;
	if (mat[2][2] > mat[i][i]) i = 2;

	switch (i) {
        case 0:
	    sclrTmp = 0.5*sqrt(1 + mat[0][0] - mat[1][1] - mat[2][2]);
	    qtn[0] = sclrTmp;
	    qtn[1] = 0.25*(mat[0][1] + mat[1][0])/sclrTmp;
	    qtn[2] = 0.25*(mat[0][2] + mat[2][0])/sclrTmp;
	    qtn[3] = 0.25*(mat[1][2] - mat[2][1])/sclrTmp;
	    break;

        case 1:
	    sclrTmp = 0.5*sqrt(1 - mat[0][0] + mat[1][1] - mat[2][2]);
	    qtn[0] = 0.25*(mat[1][0] + mat[0][1])/sclrTmp;
	    qtn[1] = sclrTmp;
	    qtn[2] = 0.25*(mat[1][2] + mat[2][1])/sclrTmp;
	    qtn[3] = 0.25*(mat[2][0] - mat[0][2])/sclrTmp;
	    break;

        case 2:
	    sclrTmp = 0.5*sqrt(1 - mat[0][0] - mat[1][1] + mat[2][2]);
	    qtn[0] = 0.25*(mat[2][0] + mat[0][2])/sclrTmp;
	    qtn[1] = 0.25*(mat[2][1] + mat[1][2])/sclrTmp;
	    qtn[2] = sclrTmp;
	    qtn[3] = 0.25*(mat[0][1] - mat[1][0])/sclrTmp;
	    break;
        }
    }

    return qtn;
}

//! dtkAxisAngleFromQuaternion( const dtkQuaternion<T> &qtn )
/*! 
 * This function duplicates dtkEulerAxisFromQuaternion(qtn) it only has
 * a different return type.
*/
template <class T> dtkVector<T> dtkAxisAngleFromQuaternion(const dtkQuaternion<T>& qtn)
{
    return dtkEulerAxisFromQuaternion(qtn);
}

//! dtkQuaternionFromAxisAngle( const dtkVector<T> &axis, const T angle )
/*! 
* This function duplicates dtkQuaternionFromEulerAxisAndAngle(..) it
* only has a different function profile.
*/
template <class T> dtkQuaternion<T> dtkQuaternionFromAxisAngle( const dtkVector<T> &axis,
                                                                const T angle )
{
    return dtkQuaternionFromEulerAxisAndAngle(dtkVector3D<T>(axis), angle);
}

//! dtkChangeOfBasis(dtkVector3D< dtkVector3D<T> >&from, dtkVector3D< dtkVector3D<T> >&to)
/*!
 * This is a "change of basis" from the "from" frame to the "to"
 * frame.  the "to" frame is typically the "Standard basis" frame.
 * The "from" is a frame that represents the current orientation
 * of the object in the shape of an orthonormal tripod.
*/
template <class T> dtkMatrixSquared<T> dtkChangeOfBasis(dtkVector3D< dtkVector3D<T> >&from, 
                                                        dtkVector3D< dtkVector3D<T> >&to)
{
    dtkMatrixSquared<T> A( 3 );
    enum { x , y , z };

    // _X,_Y,_Z is typically the standard basis frame.

    //  | x^_X , y^_X , z^_X |
    //  | x^_Y , y^_Y , z^_Y |
    //  | x^_Z , y^_Z , z^_Z |
	
    A[0][0] = from[x]*to[x];
    A[0][1] = from[y]*to[x];
    A[0][2] = from[z]*to[x];

    A[1][0] = from[x]*to[y];
    A[1][1] = from[y]*to[y];
    A[1][2] = from[z]*to[y];

    A[2][0] = from[x]*to[z];
    A[2][1] = from[y]*to[z];
    A[2][2] = from[z]*to[z];
	
    // This is simply the transpose done manually which would save
    // and inverse call.
    //	| x ^ _X , x ^ _Y , x ^ _Z |
    //	| y ^ _X , y ^ _Y , y ^ _Z |
    //	| z ^ _X , z ^ _Y , z ^ _Z |
	
    // And finally we return the matrix that takes the "from" frame
    // to the "to"/"Standard basis" frame.
    return A;
}

#endif

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

// $Id: coordsys.h 165 2008-01-19 19:53:19Z hkuiper $

// CwMtx matrix and vector math library
// Copyright (C) 1999-2001  Harry Kuiper
// Copyright (C) 2000  Will DeVore (template conversion)

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
