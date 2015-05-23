#include "numberlib.h"

static unsigned int gcd(unsigned int smaller, unsigned int bigger);

unsigned int greatestCommonDivisor(unsigned int m, unsigned int n)
{
    if( m <= 0 || n <= 00 ){
        return 0;
    }
    if( m < n ){
        return gcd(m,n);
    }
    else{
        return gcd(n,m);
    }
}

static unsigned int gcd(unsigned int smaller, unsigned int bigger)
{
    if( smaller == 0 )
        return bigger;
    else
        return gcd( bigger % smaller, smaller );
}
