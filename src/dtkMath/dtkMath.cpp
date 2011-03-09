/* dtkMath.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jul  6 16:57:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar  9 14:17:25 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 37
 */

/* Commentary: 
 * 
 * fabs - ok with doubles as well
 * 
 */

/* Change log:
 * 
 */

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

//! 
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

//! 
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

//! 
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

//! 
/*! 
 * 
 */
bool dtkAlmostEqualUlps(float A, float B, int maxUlps)
{
    if (A == B)
        return true; 

    int intDiff = abs(*(int*)&A - *(int*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlps(double A, double B, long long int maxUlps)
{
    if (A == B)
        return true; 

    long long int intDiff = abs(*(long long int*)&A - *(long long int*)&B);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

//! 
/*! 
 * 
 */
bool dtkAlmostEqual2sComplement(float A, float B, int maxUlps)
{
    //assert(maxUlps > 0 && maxUlps <= 16 * 1024 * 1024);

    int aInt = *(int*)&A;
    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    long long int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqual2sComplement(double A, double B, long long int maxUlps)
{
    //assert(maxUlps > 0 && maxUlps <= 16 * 1024 * 1024);

    long long int aInt = *(long long int*)&A;
    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;

    long long int bInt = *(long long int*)&B;
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;

    long long int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define INFINITYCHECK
#define NANCHECK
#define SIGNCHECK

//! 
/*! 
 * 
 */
inline bool dtkIsInfinite(float A)
{
    const int kInfAsInt = 0x7F800000;

    if ((*(int*)&A & 0x7FFFFFFF) == kInfAsInt)
        return true;

    return false;
}

inline bool dtkIsInfinite(double A)
{
    const long long int kInfAsInt = 0x7F80000000000000;

    if ((*(long long int*)&A & 0x7FFFFFFFFFFFFFFF) == kInfAsInt)
        return true;

    return false;
}

//! 
/*! 
 * 
 */
inline bool dtkIsNan(float A)
{
    int exp = *(int*)&A & 0x7F800000;
    int mantissa = *(int*)&A & 0x007FFFFF;

    if (exp == 0x7F800000 && mantissa != 0)
        return true;

    return false;
}

inline bool dtkIsNan(double A)
{
    long long int exp = *(long long int*)&A & 0x7F80000000000000;
    long long int mantissa = *(long long int*)&A & 0x007FFFFFFFFFFFFF;

    if (exp == 0x7F80000000000000 && mantissa != 0)
        return true;

    return false;
}

//! 
/*! 
 * 
 */
inline int dtkSign(float A)
{
    return (*(int*)&A) & 0x80000000;
}

inline long long int dtkSign(double A)
{
    return (*(long long int*)&A) & 0x8000000000000000;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

//! 
/*! 
 * 
 */
bool dtkAlmostEqualUlpsFinal(float A, float B, int maxUlps)
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

    int aInt = *(int*)&A;

    if (aInt < 0)
        aInt = 0x80000000 - aInt;

    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkAlmostEqualUlpsFinal(double A, double B, long long int maxUlps)
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

    long long int aInt = *(long long int*)&A;

    if (aInt < 0)
        aInt = 0x8000000000000000 - aInt;

    long long int bInt = *(long long int*)&B;
    if (bInt < 0)
        bInt = 0x8000000000000000 - bInt;

    long long int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

//! 
/*! 
 * 
 */
void dtkPrintNumber(float f, int offset)
{
    (*((int*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%08lX, %d\n", f, *(int*)&f, *(int*)&f);
#else
    printf("%+1.8g, %d, %d\n", f, *(int*)&f, *(int*)&f);
#endif
}

void dtkPrintNumber(double f, long long int offset)
{
    (*((long long int*)&f)) += offset;

#if !defined(__APPLE__)
    printf("%+1.8g, 0x%08lX, %lld\n", f, *(long long int*)&f, *(long long int*)&f);
#else
    printf("%+1.8g, %lld, %lld\n", f, *(long long int*)&f, *(long long int*)&f);
#endif
}

