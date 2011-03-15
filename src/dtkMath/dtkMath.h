/* dtkMath.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jun  8 15:37:50 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 15 16:56:08 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 177
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

#include <inttypes.h>

DTKMATH_EXPORT void dtkBubbleSort(unsigned int indices[], int size);

DTKMATH_EXPORT bool dtkAlmostEqualRelative( float A,  float B,  float maxRelativeError);
DTKMATH_EXPORT bool dtkAlmostEqualRelative(double A, double B, double maxRelativeError);

DTKMATH_EXPORT bool dtkAlmostEqualRelative2( float A,  float B,  float maxRelativeError);
DTKMATH_EXPORT bool dtkAlmostEqualRelative2(double A, double B, double maxRelativeError);

DTKMATH_EXPORT bool dtkAlmostEqualRelativeOrAbsolute( float A,  float B,  float maxRelativeError,  float maxAbsoluteError);
DTKMATH_EXPORT bool dtkAlmostEqualRelativeOrAbsolute(double A, double B, double maxRelativeError, double maxAbsoluteError);

DTKMATH_EXPORT bool dtkAlmostEqualUlpsSimple( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqualUlpsSimple(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT bool dtkAlmostEqual2sComplement( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqual2sComplement(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT bool dtkIsInfinite( float A);
DTKMATH_EXPORT bool dtkIsInfinite(double A);

DTKMATH_EXPORT bool dtkIsNan( float A);
DTKMATH_EXPORT bool dtkIsNan(double A);

DTKMATH_EXPORT int_least32_t dtkSign( float A);
DTKMATH_EXPORT int_least64_t dtkSign(double A);

DTKMATH_EXPORT bool dtkAlmostEqualUlps( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkAlmostEqualUlps(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT void dtkPrintNumber( float f, int_least32_t offset);
DTKMATH_EXPORT void dtkPrintNumber(double f, int_least64_t offset);

DTKMATH_EXPORT bool dtkLesserThanUlps( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkLesserThanUlps(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT bool dtkLesserThanOrAlmostEqualUlps( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkLesserThanOrAlmostEqualUlps(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT bool dtkGreaterThanUlps( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkGreaterThanUlps(double A, double B, int_least64_t maxUlps);

DTKMATH_EXPORT bool dtkGreaterThanOrAlmostEqualUlps( float A,  float B, int_least32_t maxUlps);
DTKMATH_EXPORT bool dtkGreaterThanOrAlmostEqualUlps(double A, double B, int_least64_t maxUlps);

#include "dtkMath.tpp"

#endif
