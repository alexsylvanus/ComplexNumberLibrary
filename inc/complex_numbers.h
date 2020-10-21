/* File: complex_numbers.h
 * Author: Alex Sylvanus
 * Description: Declares the complex number structures and functions
 * 
*/

/* Begin Header */
#ifndef COMPLEX_NUMBERS_H_
#define COMPLEX_NUMBERS_H_

/* Includes */

/* Type Definitions */
typedef struct { /* Default Complex Type */
    double real;
    double imaginary;
} complex_t;

typedef struct { /* Double Complex Type */
    float real;
    float imaginary;
} fcomplex_t;

/* Functions */

/* Complex Specific */
double Radius(complex_t z);
double Phase(complex_t z);

/* Binary Operators */
complex_t cAdd(complex_t z1, complex_t z2);
complex_t cSub(complex_t z1, complex_t z2);
complex_t cMul(complex_t z1, complex_t z2);
complex_t cDiv(complex_t z1, complex_t z2);
complex_t cPow(complex_t z1, complex_t z2);

/* Trancendental Functions */
complex_t cExp(complex_t z);
complex_t cLn(complex_t z);
complex_t cSin(complex_t z);
complex_t cCos(complex_t z);
complex_t cTan(complex_t z);
complex_t cNgtv(complex_t z);

/* Polar Functions */
complex_t cAbs(complex_t z);
complex_t cPhi(complex_t z);

/* Multivariable functions */
complex_t cAvg(complex_t z1, complex_t z2);

/* Output */
void printComplex(complex_t z);
void printComplexLine(complex_t z);

#endif /* COMPLEX_NUMBERS_H_ */