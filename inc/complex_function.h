/* File: complex_function.h
 * Author: Alex Sylvanus
 * Description: Declares the the struct for a complex_function
 * 
*/

/* Begin Header */
#ifndef COMPLEX_FUNCTION_H_
#define COMPLEX_FUNCTION_H_

/* Includes */
#include "complex_vector.h"
#include "C:/GCC_Projects/VectorLibrary/vector_library.h"

/* Struct */
typedef struct {
    vstring_t fstack;
    string_t fstring;
} complexFunction_t;

/* Functions */
complexFunction_t initFunc(string_t s);
vstring_t parseFunction(string_t s);
complex_t compute(complexFunction_t f, complex_t z);

#endif /* COMPLEX_FUNCTION_H_ */