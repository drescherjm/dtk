/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar  9 14:08:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jun 30 13:30:12 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include <dtkCore/dtkGlobal.h>

#include <dtkMath/dtkMath.h>

#include <float.h>
#include <math.h>
#include <stdio.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int TestCompare2sComplement(double A, double B, bool expectedResult, long long int maxUlps = 10)
{
    bool result = dtkAlmostEqual2sComplement(A, B, maxUlps);

    if (result != expectedResult) {
        printf("Unexpected result - %1.18f, %1.18f, %lld, expected %s\n", A, B, maxUlps, expectedResult ? "true" : "false");
        return DTK_FAILURE;
    }

    return DTK_SUCCEED;
}

int TestCompareFinal(double A, double B, bool expectedResult, long long int maxUlps = 10)
{
    bool result = dtkAlmostEqualUlps(A, B, maxUlps);

    if (result != expectedResult) {
        printf("Unexpected result final - %1.18f, %1.18f, %lld, expected %s\n", A, B, maxUlps, expectedResult ? "true" : "false");
        return DTK_FAILURE;
    }

    return DTK_SUCCEED;
}

int TestCompareAll(double A, double B, bool expectedResult, long long int maxUlps = 10)
{
    if (TestCompare2sComplement(A, B, expectedResult, maxUlps) ||
        TestCompareFinal(A, B, expectedResult, maxUlps))
        return DTK_FAILURE;

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

double zero1 = 0;
double zero2 = 0;

int main(int argc, char* argv[])
{
    double negativeZero;
        
    *(long long int*)&negativeZero = 0x8000000000000000LL;
    
    double nan1 = sqrt(-1.0);
    double nan2 = zero1 / zero2;
    double inf0 = 1 / zero1;
    double nan3 = inf0 - inf0;
    double nan4 = nan3; (*(long long int*)&nan4) += 1;
    double smallestDenormal = 0; (*(long long int*)&smallestDenormal) += 1;

    Q_UNUSED(nan1);
    
    int status = 0;

    printf("01 - \n"); status  = TestCompareAll(zero1, negativeZero, true);
    printf("02 - \n"); status += TestCompareAll(2.0, 1.999999999999999, true);
    printf("03 - \n"); status += TestCompareAll(2.0, 1.9999999999999995, true);
    printf("04 - \n"); status += TestCompareAll(1.9999999999999995, 2.0, true);
    printf("05 - \n"); status += TestCompareAll(2.0, 1.9999999999999995, true);
    printf("06 - \n"); status += TestCompare2sComplement(inf0, -inf0, false, 16 * 1024 * 1024);
    printf("07 - \n"); status += TestCompareFinal(inf0, -inf0, false, 16 * 1024 * 1024);
    printf("08 - \n"); status += TestCompare2sComplement(DBL_MAX, inf0, true);
    printf("09 - \n"); status += TestCompareFinal(DBL_MAX, inf0, false);
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
