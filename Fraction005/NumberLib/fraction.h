#ifndef FRACTION_H
#define FRACTION_H

#define FRACTION_OK 0
#define FRACTION_ERROR_ZERO_DENOMINATOR 1
#define FRACTION_ERROR_OVERFLOW 2

extern int fractionMuliply(
        int sign1, unsigned int numerator1, unsigned int denominator1,
        int sign2, unsigned int numerator2, unsigned int denominator2,
        int *sign3, unsigned int *numerator3, unsigned int *denominator3
        );

#endif // FRACTION_H

