/* dtkMath.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jun  8 15:37:50 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 16 10:47:05 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 187
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKMATH_H
#define DTKMATH_H

#include "dtkMathExport.h"

#include <QtCore/QtGlobal>

#if !defined(Q_WS_WIN)
#include <inttypes.h>
#else
#define int32_t __int32
#define int64_t __int64
#endif

// /////////////////////////////////////////////////////////////////
// Sorting algorithm
// /////////////////////////////////////////////////////////////////

DTKMATH_EXPORT void dtkBubbleSort(unsigned int indices[], int size);

// /////////////////////////////////////////////////////////////////
// Some bit constants 
// /////////////////////////////////////////////////////////////////

#define ONE_BIT_32 (1u)
#define HIGH_BIT_32 ((1u)<<31)
#define EXP_255_BIT_32 (255u<<23)

#define ONE_BIT_64 (1ull)
#define HIGH_BIT_64 ((1ull)<<63)
#define EXP_255_BIT_64 (255ull<<55)

// /////////////////////////////////////////////////////////////////
// Float and double comparisons
// /////////////////////////////////////////////////////////////////

DTKMATH_EXPORT bool dtkAlmostEqualRelative( float A,  float B,  float maxRelativeError);
DTKMATH_EXPORT bool dtkAlmostEqualRelative(double A, double B, double maxRelativeError);

DTKMATH_EXPORT bool dtkAlmostEqualRelative2( float A,  float B,  float maxRelativeError);
DTKMATH_EXPORT bool dtkAlmostEqualRelative2(double A, double B, double maxRelativeError);

DTKMATH_EXPORT bool dtkAlmostEqualRelativeOrAbsolute( float A,  float B,  float maxRelativeError,  float maxAbsoluteError);
DTKMATH_EXPORT bool dtkAlmostEqualRelativeOrAbsolute(double A, double B, double maxRelativeError, double maxAbsoluteError);

DTKMATH_EXPORT bool dtkAlmostEqualUlpsSimple( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqualUlpsSimple(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT bool dtkAlmostEqual2sComplement( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqual2sComplement(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT bool dtkIsInfinite( float A);
DTKMATH_EXPORT bool dtkIsInfinite(double A);

DTKMATH_EXPORT bool dtkIsNan( float A);
DTKMATH_EXPORT bool dtkIsNan(double A);

DTKMATH_EXPORT int32_t dtkSign( float A);
DTKMATH_EXPORT int64_t dtkSign(double A);

DTKMATH_EXPORT bool dtkAlmostEqualUlps( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqualUlps(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT void dtkPrintNumber( float f, int32_t offset);
DTKMATH_EXPORT void dtkPrintNumber(double f, int64_t offset);

DTKMATH_EXPORT bool dtkLesserThanUlps( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkLesserThanUlps(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT bool dtkLesserThanOrAlmostEqualUlps( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkLesserThanOrAlmostEqualUlps(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT bool dtkGreaterThanUlps( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkGreaterThanUlps(double A, double B, int64_t maxUlps);

DTKMATH_EXPORT bool dtkGreaterThanOrAlmostEqualUlps( float A,  float B, int32_t maxUlps);
DTKMATH_EXPORT bool dtkGreaterThanOrAlmostEqualUlps(double A, double B, int64_t maxUlps);

#include "dtkMath.tpp"

#endif
