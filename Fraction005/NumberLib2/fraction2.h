#ifndef FRACTION2_H
#define FRACTION2_H

enum fraction_status {
    FRACTION_OK,
    FRACTION_ERROR_DENOMINATOR_ZERO,
    FRACTION_ERROR_OVERFLOW
};

struct fraction {
    int sign;
    unsigned int numerator;
    unsigned int denominator;
    enum fraction_status status;
};

extern struct fraction fractionMultiply(
        struct fraction f1,
        struct fraction f2 );

#endif // FRACTION2_H
