/* dtkMath.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jul  6 16:57:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 15 17:35:34 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 111
 */

/* Commentary: 
 * 
 * fabs - ok with doubles as well
 * 
 * Comparison between float and between double is derived from the
 * work of Bruce Dawson available here:
 *
 * http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
 * 
 */

/* Change log:
 * 
 */

#include "dtkConfig.h"
#include "dtkMath.h"
#include "dtkVector3D.h"

//! dtkBubbleSort(unsigned int indices[], int size) 
/*! 
 * Sorts the integer of an array by growing values.
 */
void dtkBubbleSort(unsigned int indices[], int size) 
{
    bool ordered = false;
    int j = 0;
    while ( (j<size-1) && (!ordered) ) {
        ordered = true;
        for (int k = 0; k<(size-1-j); k++) {
            if (indices[k] > indices[k+1]) {
                unsigned int temp = indices[k];
                indices[k] = indices[k+1];
                indices[k+1] = temp;
                ordered = false;
            }
        }
        j++;
    }
}

//! Non-optimal AlmostEqual function - not recommended.
/*! 
 * 
 */
bool dtkAlmostEqualRelative(float A, float B, float maxRelativeError)
{
    if (A == B)
        return true;

    float relativeError = fabs((A - B) / B);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

bool dtkAlmostEqualRelative(double A, double B, double maxRelativeError)
{
    if (A == B)
        return true;

    double relativeError = fabs((A - B) / B);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

//! Slightly better AlmostEqual function but still not recommended
/*! 
 * 
 */
bool dtkAlmostEqualRelative2(float A, float B, float maxRelativeError)
{
    if (A == B)
        return true;

    float relativeError;

    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

bool dtkAlmostEqualRelative2(double A, double B, double maxRelativeError)
{
    if (A == B)
        return true;

    double relativeError;

    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

//! Slightly better AlmostEqual function and still not recommended
/*! 
 * 
 */
bool dtkAlmostEqualRelativeOrAbsolute(float A, float B, float maxRelativeError, float maxAbsoluteError)
{
    if (fabs(A - B) < maxAbsoluteError)
        return true;

    float relativeError;

    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

bool dtkAlmostEqualRelativeOrAbsolute(double A, double B, double maxRelativeError, double maxAbsoluteError)
{
    if (fabs(A - B) < maxAbsoluteError)
        return true;

    double relativeError;

    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);

    if (relativeError <= maxRelativeError)
        return true;

    return false;
}

//! Initial AlmostEqualULPs version.
/*! 
 *  Fast and simple, but some limitations.
 */
bool dtkAlmostEqualUlpsSimple(float A, float B, int_least32_t maxUlps)
{
    if (A == B)
        return true; 

    int_least32_t intDiff = abs(*(int_least32_t*)&A - *(int_least32_t*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlpsSimple(double A, double B, int_least64_t maxUlps)
{
    if (A == B)
        return true; 

    int_least64_t intDiff = abs(*(int_least64_t*)&A - *(int_least64_t*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

//! Usable AlmostEqual function.
/*! 
 * 
 */
bool dtkAlmostEqual2sComplement(float A, float B, int_least32_t maxUlps)
{
    if (maxUlps < 0 || maxUlps > 4 * 1024 * 1024)
        return false;

    int_least32_t aInt = *(int_least32_t*)&A;
    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int_least32_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqual2sComplement(double A, double B, int_least64_t maxUlps)
{
    if (maxUlps < 0 || maxUlps > 8 * 1024 * 1024)
        return false;

    int_least64_t aInt = *(int_least64_t*)&A;
    if (aInt < 0)
#if defined(DTK_PLATFORM_64)
        aInt = 0x8000000000000000 - aInt;
#else
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;
    if (bInt < 0)
#if defined(DTK_PLATFORM_64)
        bInt = 0x8000000000000000 - bInt;
#else
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

// /////////////////////////////////////////////////////////////////
// Support functions and conditional compilation directives for the
// master AlmostEqual function.
// ////////////////////////////////////////////////////////////////

#define INFINITYCHECK
#define NANCHECK
#define SIGNCHECK

//! Is \a A infinite.
/*! 
 *  An infinity has an exponent of 255 (shift left 23 positions) and a
 *  zero mantissa. There are two infinities - positive and negative.
 */
inline bool dtkIsInfinite(float A)
{
    const int_least32_t kInfAsInt = 0x7F800000;

    if ((*(int_least32_t*)&A & 0x7FFFFFFF) == kInfAsInt)
        return true;

    return false;
}

inline bool dtkIsInfinite(double A)
{
    const int_least64_t kInfAsInt = 0x7F80000000000000;

#if defined (DTK_PLATFORM_64)
    if ((*(int_least64_t*)&A & 0x7FFFFFFFFFFFFFFF) == kInfAsInt)
        return true;
#else
    if ((*(int_least64_t*)&A & 0x7FFFFFFF) == kInfAsInt)
        return true;
#endif

    return false;
}

//! Is \a A NAN.
/*! 
 *  A NAN has an exponent of 255 (shifted left 23 positions) and a
 *  non-zero mantissa.
 */
inline bool dtkIsNan(float A)
{
    int_least32_t exp = *(int_least32_t*)&A & 0x7F800000;
    int_least32_t mantissa = *(int_least32_t*)&A & 0x007FFFFF;

    if (exp == 0x7F800000 && mantissa != 0)
        return true;

    return false;
}

inline bool dtkIsNan(double A)
{
#if defined(DTK_PLATFORM_64)
    int_least64_t exp = *(int_least64_t*)&A & 0x7F80000000000000;
    int_least64_t mantissa = *(int_least64_t*)&A & 0x007FFFFFFFFFFFFF;
#else
    int_least64_t exp = *(int_least64_t*)&A & 0x7F800000;
    int_least64_t mantissa = *(int_least64_t*)&A & 0x007FFFFF;
#endif

    if (exp == 0x7F80000000000000 && mantissa != 0)
        return true;

    return false;
}

//! Returns the sign of \a A.
/*! 
 *  The sign bit of a number is the high bit.
 */
inline int_least32_t dtkSign(float A)
{
    return (*(int_least32_t*)&A) & 0x80000000;
}

inline int_least64_t dtkSign(double A)
{
#if defined(DTK_PLATFORM_64)
    return (*(int_least64_t*)&A) & 0x8000000000000000;
#else
    return (*(int_least64_t*)&A) & 0x80000000;
#endif
}

//! Final version of the AlmostEqualUlps function.
/*! 
 *  The optional checks are included for completeness, but in many
 *  cases they are not necessary, or even not desirable.
 *
 *  If A or B are infinity (positive or negative) then only return true
 *  if they are exactly equal to each other - that is, if they are both
 *  infinities of the same sign. This check is only needed if you will
 *  be generating infinities and you don't want them 'close' to numbers
 *  near FLT_MAX.
 *
 *  If A or B are a NAN, return false. NANs are equal to nothing, not
 *  even themselves. This check is only needed if you will be
 *  generating NANs and you use a maxUlps greater than 4 million or
 *  you want to ensure that a NAN does not equal itself.
 *
 *  After adjusting floats so their representations are
 *  lexicographically ordered as twos-complement integers a very small
 *  positive number will compare as 'close' to a very small negative
 *  number. If this is not desireable, and if you are on a platform
 *  that supports subnormals (which is the only place the problem can
 *  show up) then you need this check. The check for A == B is because
 *  zero and negative zero have different signs but are equal to each
 *  other.
 *
 */
bool dtkAlmostEqualUlps(float A, float B, int_least32_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A == B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A == B;
#endif

    int_least32_t aInt = *(int_least32_t*)&A;

    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    // Make bInt lexicographically ordered as a twos-complement int
    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    int_least32_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlps(double A, double B, int_least64_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A == B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A == B;
#endif

    int_least64_t aInt = *(int_least64_t*)&A;

#if defined(DTK_PLATFORM_64)
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;
#else
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;

#if defined(DTK_PLATFORM_64)
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;
#else
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

//! Prints a number and its representation, in hex and decimal
/*! 
 * 
 */
void dtkPrintNumber(float f, int_least32_t offset)
{
    (*((int_least32_t*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%08lX, %d\n", f, *(int_least32_t*)&f, *(int_least32_t*)&f);
#else
    printf("%+1.8g, %d, %d\n", f, *(int_least32_t*)&f, *(int_least32_t*)&f);
#endif
}

void dtkPrintNumber(double f, int_least64_t offset)
{
    (*((int_least64_t*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%08lX, %lld\n", f, *(int_least64_t*)&f, *(int_least64_t*)&f);
#else
    printf("%+1.8g, %lld, %lld\n", f, *(int_least64_t*)&f, *(int_least64_t*)&f);
#endif
}

// /////////////////////////////////////////////////////////////////
// Additional functions for further comparisons
// /////////////////////////////////////////////////////////////////

//! Returns true when \a A and \B are far apart and A smaller than B.
/*! 
 * 
 */
bool dtkLesserThanUlps(float A, float B, int_least32_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A < B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A < B;
#endif

    int_least32_t aInt = *(int_least32_t*)&A;

    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int_least32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff > 0)
        return false;

    else
        return true;    
}

bool dtkLesserThanUlps(double A, double B, int_least64_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A < B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A < B;
#endif

    int_least64_t aInt = *(int_least64_t*)&A;

#if defined(DTK_PLATFORM_64)
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;
#else
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;

#if defined(DTK_PLATFORM_64)
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;
#else
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff > 0)
        return false;

    else
        return true; 
}

//! Returns true when \a A and \B are not too far apart or A smaller than B.
/*! 
 * 
 */
bool dtkLesserThanOrAlmostEqualUlps(float A, float B, int_least32_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A <= B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A <= B;
#endif

    int_least32_t aInt = *(int_least32_t*)&A;

    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int_least32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff > 0)
        return false;

    else
        return true; 
}

bool dtkLesserThanOrAlmostEqualUlps(double A, double B, int_least64_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A <= B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A <= B;
#endif

    int_least64_t aInt = *(int_least64_t*)&A;

#if defined(DTK_PLATFORM_64)
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;
#else
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;

#if defined(DTK_PLATFORM_64)
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;
#else
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff > 0)
        return false;

    else
        return true; 
}

//! Returns true when \a A and \B are far apart and A greater than B.
/*! 
 * 
 */
bool dtkGreaterThanUlps(float A,  float B, int_least32_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A > B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A > B;
#endif

    int_least32_t aInt = *(int_least32_t*)&A;

    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int_least32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff < 0)
        return false;

    else
        return true; 
}

bool dtkGreaterThanUlps(double A, double B, int_least64_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A > B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A > B;
#endif

    int_least64_t aInt = *(int_least64_t*)&A;

#if defined(DTK_PLATFORM_64)
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;
#else
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;

#if defined(DTK_PLATFORM_64)
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;
#else
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff < 0)
        return false;

    else
        return true;
}

//! Returns true when \a A and \B are not too far apart or A greater than B.
/*! 
 * 
 */
bool dtkGreaterThanOrAlmostEqualUlps(float A,  float B, int_least32_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A >= B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A >= B;
#endif

    int_least32_t aInt = *(int_least32_t*)&A;

    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int_least32_t bInt = *(int_least32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int_least32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff < 0)
        return false;

    else
        return true;
}

bool dtkGreaterThanOrAlmostEqualUlps(double A, double B, int_least64_t maxUlps)
{
#ifdef  INFINITYCHECK
    if (dtkIsInfinite(A) || dtkIsInfinite(B))
        return A >= B;
#endif

#ifdef  NANCHECK
    if (dtkIsNan(A) || dtkIsNan(B))
        return false;
#endif

#ifdef  SIGNCHECK
    if (dtkSign(A) != dtkSign(B))
        return A >= B;
#endif

    int_least64_t aInt = *(int_least64_t*)&A;

#if defined(DTK_PLATFORM_64)
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;
#else
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
#endif

    int_least64_t bInt = *(int_least64_t*)&B;

#if defined(DTK_PLATFORM_64)
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;
#else
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
#endif

    int_least64_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff < 0)
        return false;

    else
        return true;
}

