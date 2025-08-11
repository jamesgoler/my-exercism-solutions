#include "complex_numbers.h"

#include <math.h>

complex_t c_add(complex_t a, complex_t b) {
    return (complex_t) {
        .real = a.real + b.real,
        .imag = a.imag + b.imag,
    };
}

complex_t c_sub(complex_t a, complex_t b) {
    return (complex_t) {
        .real = a.real - b.real,
        .imag = a.imag - b.imag,
    };
}

complex_t c_mul(complex_t a, complex_t b) {
    return (complex_t) {
        .real = a.real * b.real - a.imag * b.imag,
        .imag = a.real * b.imag + b.real * a.imag,
    };
}

complex_t c_div(complex_t a, complex_t b) {
    double cc_plus_dd = pow(b.real, 2) + pow(b.imag, 2);
    complex_t result = c_mul(a, c_conjugate(b));
    result.real /= cc_plus_dd;
    result.imag /= cc_plus_dd;
    return result;
}

double c_abs(complex_t x) {
   return sqrt(pow(x.real, 2) + pow(x.imag, 2));
}

complex_t c_conjugate(complex_t x) {
    return (complex_t) {
        .real = x.real,
        .imag = -x.imag,
    };
}

double c_real(complex_t x) {
    return x.real;
}

double c_imag(complex_t x) {
    return x.imag;
}

complex_t c_exp(complex_t x) {
    double expa = exp(x.real);
    return (complex_t) {
        .real = expa * cos(x.imag),
        .imag = expa * sin(x.imag),
    };
}
