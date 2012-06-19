/* dtkMath.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jul  6 16:57:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 14 14:47:52 2012 (+0200)
 *           By: tkloczko
 *     Update #: 190
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

#if defined(Q_WS_WIN)
// on vs 9 abs() does not work with long long int or __uint64
#define abs qAbs
#endif

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
        for (int k = 0; k < (size-1-j); k++) {
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

//! Sorts the integer of an array by growing values.
/*! 
 * 
 */
void dtkBubbleSort(qint32 *indices, qint32 size)
{
    bool ordered = false;
    qint32 j = 0;
    while ( (j<size-1) && (!ordered) ) {
        ordered = true;
        for (qint32 k = 0; k < (size-1-j); k++) {
            if (indices[k] > indices[k+1]) {
                qint32 temp = indices[k];
                indices[k] = indices[k+1];
                indices[k+1] = temp;
                ordered = false;
            }
        }
        j++;
    }
}

//! Sorts the integer of an array by growing values.
/*! 
 * 
 */
void dtkBubbleSort(qint64 *indices, qint64 size)
{
    bool ordered = false;
    qint64 j = 0;
    while ( (j<size-1) && (!ordered) ) {
        ordered = true;
        for (qint64 k = 0; k<(size-1-j); k++) {
            if (indices[k] > indices[k+1]) {
                qint64 temp = indices[k];
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
bool dtkAlmostEqualUlpsSimple(float A, float B, int32_t maxUlps)
{
    if (A == B)
        return true; 
 
    int32_t intDiff = abs(*(int32_t*)&A - *(int32_t*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlpsSimple(double A, double B, int64_t maxUlps)
{
    if (A == B)
        return true; 

    int64_t intDiff = labs(*(int64_t*)&A - *(int64_t*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

//! Usable AlmostEqual function.
/*! 
 * 
 */
bool dtkAlmostEqual2sComplement(float A, float B, int32_t maxUlps)
{
    if (maxUlps < 0 || maxUlps > 4 * 1024 * 1024)
        return false;

    int32_t aInt = *(int32_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    int32_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqual2sComplement(double A, double B, int64_t maxUlps)
{
    if (maxUlps < 0 || maxUlps > 8 * 1024 * 1024)
        return false;

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = labs(aInt - bInt);
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
    const int32_t kInfAsInt = EXP_255_BIT_32;

    if ((int32_t)((*(int32_t*)&A & (HIGH_BIT_32 - ONE_BIT_32))) == kInfAsInt)
        return true;

    return false;
}

inline bool dtkIsInfinite(double A)
{
    const int64_t kInfAsInt = EXP_255_BIT_64;

    if ((int64_t)((*(int64_t*)&A & (HIGH_BIT_64 - ONE_BIT_64))) == kInfAsInt)
        return true;

    return false;
}

//! Is \a A NAN.
/*! 
 *  A NAN has an exponent of 255 (shifted left 23 positions) and a
 *  non-zero mantissa.
 */
inline bool dtkIsNan(float A)
{
    int32_t exp = *(int32_t*)&A & EXP_255_BIT_32;
    int32_t mantissa = *(int32_t*)&A & ((1u<<23)-1u); //0x007FFFFF

    if (exp == EXP_255_BIT_32 && mantissa != 0)
        return true;

    return false;
}

inline bool dtkIsNan(double A)
{
    int64_t exp = *(int64_t*)&A & EXP_255_BIT_64;
    int64_t mantissa = *(int64_t*)&A & ((1ull<<55)-1ull); //0x007FFFFFFFFFFFFF

    if (exp == EXP_255_BIT_64 && mantissa != 0)
        return true;

    return false;
}

//! Returns the sign of \a A.
/*! 
 *  The sign bit of a number is the high bit.
 */
inline int32_t dtkSign(float A)
{
    return (*(int32_t*)&A) & HIGH_BIT_32;
}

inline int64_t dtkSign(double A)
{
    return (*(int64_t*)&A) & HIGH_BIT_64;
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
bool dtkAlmostEqualUlps(float A, float B, int32_t maxUlps)
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

    int32_t aInt = *(int32_t*)&A;

    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    // Make bInt lexicographically ordered as a twos-complement int
    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    int32_t intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlps(double A, double B, int64_t maxUlps)
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

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = labs(aInt - bInt);
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
void dtkPrintNumber(float f, int32_t offset)
{
    (*((int32_t*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%08lx, %d\n", f, *(int32_t*)&f, *(int32_t*)&f);
#else
    printf("%+1.8g, %d, %d\n", f, *(int32_t*)&f, *(int32_t*)&f);
#endif
}

void dtkPrintNumber(double f, int64_t offset)
{
    (*((int64_t*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%016llx, %lld\n", f, *(int64_t*)&f, *(int64_t*)&f);
#else
    printf("%+1.8g, %lld, %lld\n", f, *(int64_t*)&f, *(int64_t*)&f);
#endif
}

// /////////////////////////////////////////////////////////////////
// Additional functions for further comparisons
// /////////////////////////////////////////////////////////////////

//! Returns true when \a A and \B are far apart and A smaller than B.
/*! 
 * 
 */
bool dtkLesserThanUlps(float A, float B, int32_t maxUlps)
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

    int32_t aInt = *(int32_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    int32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff > 0)
        return false;

    else
        return true;    
}

bool dtkLesserThanUlps(double A, double B, int64_t maxUlps)
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

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = aInt - bInt;
    if (labs(intDiff) <= maxUlps)
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
bool dtkLesserThanOrAlmostEqualUlps(float A, float B, int32_t maxUlps)
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

    int32_t aInt = *(int32_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    int32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff > 0)
        return false;

    else
        return true; 
}

bool dtkLesserThanOrAlmostEqualUlps(double A, double B, int64_t maxUlps)
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

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = aInt - bInt;
    if (labs(intDiff) <= maxUlps)
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
bool dtkGreaterThanUlps(float A,  float B, int32_t maxUlps)
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

    int32_t aInt = *(int32_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    int32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return false;

    else if (intDiff < 0)
        return false;

    else
        return true; 
}

bool dtkGreaterThanUlps(double A, double B, int64_t maxUlps)
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

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = aInt - bInt;
    if (labs(intDiff) <= maxUlps)
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
bool dtkGreaterThanOrAlmostEqualUlps(float A,  float B, int32_t maxUlps)
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

    int32_t aInt = *(int32_t*)&A;

    if (aInt < 0)
        aInt = HIGH_BIT_32 - aInt;

    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_32 - bInt;

    int32_t intDiff = aInt - bInt;
    if (abs(intDiff) <= maxUlps)
        return true;

    else if (intDiff < 0)
        return false;

    else
        return true;
}

bool dtkGreaterThanOrAlmostEqualUlps(double A, double B, int64_t maxUlps)
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

    int64_t aInt = *(int64_t*)&A;
    if (aInt < 0)
        aInt = HIGH_BIT_64 - aInt;

    int64_t bInt = *(int64_t*)&B;
    if (bInt < 0)
        bInt = HIGH_BIT_64 - bInt;

    int64_t intDiff = aInt - bInt;
    if (labs(intDiff) <= maxUlps)
        return true;

    else if (intDiff < 0)
        return false;

    else
        return true;
}
