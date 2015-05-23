#include "fraction.h"
#include "numberlib.h"
#include "limits.h"

int fractionMuliply(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *sign3, unsigned int *numerator3, unsigned int *denominator3
)
{
    if( (denominator1 == 0) || (denominator2 == 0) ){
        return FRACTION_ERROR_ZERO_DENOMINATOR;
    }
    if( ((UINT_MAX / numerator1) < numerator2) ||
        ((UINT_MAX / denominator1) < denominator2) ){
        return FRACTION_ERROR_OVERFLOW;
    }

    *sign3 = sign1 * sign2;
    *numerator3 = numerator1 * numerator2;
    *denominator3 = denominator1 * denominator2;
    unsigned int gcd = greatestCommonDivisor(*numerator3,*denominator3);
    *numerator3 /= gcd;
    *denominator3 /= gcd;

    return FRACTION_OK;
}

