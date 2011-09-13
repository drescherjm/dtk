/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar  9 14:13:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jun 30 13:29:39 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkMath/dtkMath.h>

#include <dtkCore/dtkGlobal.h>

#include <float.h>
#include <math.h>
#include <stdio.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int TestCompare2sComplement(float A, float B, bool expectedResult, int maxUlps = 10)
{
    bool result = dtkAlmostEqual2sComplement(A, B, maxUlps);

    if (result != expectedResult) {
        printf("Unexpected result - %1.9f, %1.9f, %d, expected %s\n", A, B, maxUlps, expectedResult ? "true" : "false");
        return DTK_FAILURE;
    }

    return DTK_SUCCEED;
}

int TestCompareFinal(float A, float B, bool expectedResult, int maxUlps = 10)
{
    bool result = dtkAlmostEqualUlps(A, B, maxUlps);

    if (result != expectedResult) {
        printf("Unexpected result final - %1.9f, %1.9f, %d, expected %s\n", A, B, maxUlps, expectedResult ? "true" : "false");
        return DTK_FAILURE;
    }

    return DTK_SUCCEED;
}

int TestCompareAll(float A, float B, bool expectedResult, int maxUlps = 10)
{
    if (TestCompare2sComplement(A, B, expectedResult, maxUlps) || TestCompareFinal(A, B, expectedResult, maxUlps))
        return DTK_FAILURE;

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

float zero1 = 0;
float zero2 = 0;

int main(int argc, char* argv[])
{
    float negativeZero;

    *(int*)&negativeZero = 0x80000000;

    float nan1 = sqrt(-1.0f);
    float nan2 = zero1 / zero2;
    float inf0 = 1 / zero1;
    float nan3 = inf0 - inf0;
    float nan4 = nan3; (*(int*)&nan4) += 1;
    float smallestDenormal = 0; (*(int*)&smallestDenormal) += 1;

    int status = 0;

    printf("01 - \n"); status  = TestCompareAll(zero1, negativeZero, true);
    printf("02 - \n"); status += TestCompareAll(2.0, 1.99999999, true);
    printf("03 - \n"); status += TestCompareAll(2.0, 1.99999995, true);
    printf("04 - \n"); status += TestCompareAll(1.99999995, 2.0, true);
    printf("05 - \n"); status += TestCompareAll(2.0, 1.99999995, true);
    printf("06 - \n"); status += TestCompare2sComplement(inf0, -inf0, false, 16 * 1024 * 1024);
    printf("07 - \n"); status += TestCompareFinal(inf0, -inf0, false, 16 * 1024 * 1024);
    printf("08 - \n"); status += TestCompare2sComplement(FLT_MAX, inf0, true);
    printf("09 - \n"); status += TestCompareFinal(FLT_MAX, inf0, false);
    printf("10 - \n"); status += TestCompare2sComplement(nan2, nan2, true);
    printf("11 - \n"); status += TestCompareFinal(nan2, nan2, false);
    printf("12 - \n"); status += TestCompare2sComplement(nan2, nan3, true);
    printf("13 - \n"); status += TestCompareFinal(nan2, nan3, false);
    printf("14 - \n"); status += TestCompare2sComplement(smallestDenormal, -smallestDenormal, true);
    printf("15 - \n"); status += TestCompareFinal(smallestDenormal, -smallestDenormal, false);

    if (status)
        return DTK_FAILURE;

    return DTK_SUCCEED;
}
