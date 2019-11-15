/* File: complex_numbers.c
 * Author: Alex Sylvanus
 * Description: Declares the complex number structures and functions
 * 
*/

/* Includes */
#include <math.h>
#include <stdio.h>
#include "../inc/complex_numbers.h"

/* Defines */
#define MAX_NUM HUGE_VAL

/* Functions */

/* Complex Specific */
double Radius(complex_t z) {
    return sqrt(z.real*z.real + z.imaginary*z.imaginary);
}
double Phase(complex_t z) {
    return atan2(z.imaginary, z.real);
}

/* Binary Operators */
complex_t cAdd(complex_t z1, complex_t z2) {
    /* Declare return variable */
    complex_t z;

    /* Assign values to complex parts */
    z.real = z1.real + z2.real;
    z.imaginary = z1.imaginary + z2.imaginary;

    return z;
}
complex_t cSub(complex_t z1, complex_t z2) {
    /* Declare return variable */
    complex_t z;

    /* Assign values to complex parts */
    z.real = z1.real - z2.real;
    z.imaginary = z1.imaginary - z2.imaginary;

    return z;
}
complex_t cMul(complex_t z1, complex_t z2) {
    /* Declare return variable */
    complex_t Z;

    /* Declare local variables */
    double radius = Radius(z1)*Radius(z2);
    double angle = Phase(z1) + Phase(z2);

    /* Assign values to complex parts */
    Z.real = radius*cos(angle);
    Z.imaginary = radius*sin(angle);

    return Z;
}
complex_t cDiv(complex_t z1, complex_t z2) {
    /* Declare return variable */
    complex_t Z;

    /* Declare local variables */
    double denom = Radius(z2);
    double radius;
    double angle;

    /* Check for division by zero */
    if (denom != 0) {
        radius = Radius(z1)/denom;
        angle = Phase(z1) - Phase(z2);
    }
    else {
        radius = MAX_NUM;
        angle = Phase(z1);
    }

    /* Assign values to complex parts */
    Z.real = radius*cos(angle);
    Z.imaginary = radius*sin(angle);

    return Z;
}
complex_t cPow(complex_t z1, complex_t z2) {
    /* Declare return variable */
    complex_t Z;

    /* Declare local variables */
    double radius = pow(Radius(z1), z2.real)*exp(-Phase(z1)*z2.imaginary);
    double angle = Phase(z1)*z2.real + log(Radius(z1))*z2.imaginary;

    /* Assign values to complex parts */
    Z.real = radius*cos(angle);
    Z.imaginary = radius*sin(angle);

    return Z;
}

/* Trancendental Functions */
complex_t cExp(complex_t z) {
    /* Declare return variable */
    complex_t Z;

    /* Declare local variables */
    double radius = exp(z.real);
    double angle = z.imaginary;

    /* Assign values to complex parts */
    Z.real = radius*cos(angle);
    Z.imaginary = radius*sin(angle);

    return Z;
}
complex_t cLn(complex_t z) {
    /* Declare return variable */
    complex_t Z;

    /* Assign values to complex parts */
    Z.real = log(Radius(z));
    Z.imaginary = Phase(z);

    return Z;
}
complex_t cSin(complex_t z) {
    /* Declare return variable */
    complex_t Z;

    /* Assign values to complex parts */
    Z.real = sin(z.real)*cosh(z.imaginary);
    Z.imaginary = -cos(z.real)*sinh(z.imaginary);

    return Z;
}
complex_t cCos(complex_t z) {
    /* Declare return variable */
    complex_t Z;

    /* Assign values to complex parts */
    Z.real = cos(z.real)*cosh(z.imaginary);
    Z.imaginary = sin(z.real)*sinh(z.imaginary);

    return Z;
}
complex_t cTan(complex_t z) {
    /* Declare variables */
    complex_t Z;
    double denom = 1+tan(z.real)*tan(z.real)*tanh(z.imaginary)*tanh(z.imaginary);

    /* Assign values to complex parts */
    Z.real = (1-tanh(z.imaginary)*tanh(z.imaginary))*tan(z.real)/denom;
    Z.imaginary = (1+tan(z.real)*tan(z.real))*tanh(z.imaginary)/denom;

    return Z;
}
complex_t cNgtv(complex_t z) {
    // Declare variables
    complex_t Z;

    // Assign values
    Z.real = -z.real;
    Z.imaginary = -z.imaginary;

    // Return value
    return Z;
}

// Polar functions
complex_t cAbs(complex_t z) {
    // Declare variables
    complex_t Z;

    // Assign values
    Z.real = (float)Radius(z);
    Z.imaginary = 0;

    // Return value
    return Z;
}
complex_t cPhi(complex_t z) {
    // Declare variables
    complex_t Z;

    // Assign values
    Z.real = (float)Phase(z);
    Z.imaginary = 0;

    // Return value
    return Z;
}

/* Output */
void printComplex(complex_t z) {
    /* Check if imaginary part is negative */
    if (z.imaginary >= 0) {
        printf("%0.3f + %0.3fi", z.real, z.imaginary);
    }
    else {
        printf("%0.3f - %0.3fi", z.real, -z.imaginary);
    } 
}
void printComplexLine(complex_t z) {
    /* Check if imaginary part is negative */
    if (z.imaginary >= 0) {
        printf("%0.3f + %0.3fi\n", z.real, z.imaginary);
    }
    else {
        printf("%0.3f - %0.3fi\n", z.real, -z.imaginary);
    }
}