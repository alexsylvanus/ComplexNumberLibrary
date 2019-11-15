/* File: complex_vector.h
 * Author: Alex Sylvanus
 * Description: Declares the complex vector structure and functions
 * 
*/

/* Begin Header */
#ifndef CPRIVATETYPES_H_
#define CPRIVATETYPES_H_

/* Includes */
#include <stdlib.h>
#include "complex_numbers.h"

/* Defines */
#define EMPTY {NULL, 0}

/* Type Definitions */
typedef struct VCMPLX Vcomplex_t;

/* Structures */
struct VCMPLX {
    complex_t* vcomplex;
    size_t length;
};

#endif /* CPRIVATETYPES_H_ */