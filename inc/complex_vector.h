/* File: complex_vector.h
 * Author: Alex Sylvanus
 * Description: Declares the complex vector structure and functions
 * 
*/

/* Begin header */
#ifndef COMPLEX_VECTOR_H_
#define COMPLEX_VECTOR_H_

/* Includes */
#include "complex_numbers.h"
#include <stdlib.h>

/* Type Definitions */
typedef struct VCMPLX* vcomplex_t;

/* Functions */
vcomplex_t zInitEmpty();
void pushz(vcomplex_t vector, complex_t value);
complex_t popz(vcomplex_t vector);
void clearz(vcomplex_t vector);
complex_t getZ(vcomplex_t vector, int index);
void vPrintZ(vcomplex_t vector);
size_t zLength(vcomplex_t vector);

#endif /* COMPLEX_VECTOR_H_ */