#include "fraction2.h"
#include "numberlib2.h"
#include "limits.h"

struct fraction fractionMultiply(
        struct fraction f1,
        struct fraction f2 )
{
    struct fraction f3 = {1,0u,1u,FRACTION_OK};

    if( f1.status != FRACTION_OK )
        return f1;
    if( f2.status != FRACTION_OK )
        return f2;

    if( (f1.denominator == 0) || (f2.denominator == 0) ){
        f3.status = FRACTION_ERROR_DENOMINATOR_ZERO;
        return f3;
    }
    if( ((UINT_MAX / f1.denominator) < f2.denominator) ||
            ((UINT_MAX / f1.numerator) < f2.numerator) ){
        f3.status = FRACTION_ERROR_OVERFLOW;
        return f3;
    }

    f3.sign = f1.sign * f2.sign;
    f3.numerator = f1.numerator * f2.numerator;
    f3.denominator = f1.denominator * f2.denominator;
    unsigned int gcd = greatestCommonDivisor( f3.numerator, f3.denominator );
    f3.numerator /= gcd;
    f3.denominator /= gcd;
    return f3;
}
