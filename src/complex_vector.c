/* File: complex_vector.c
 * Author: Alex Sylvanus
 * Description: Defines the complex vector functions
 * 
*/

/* Includes */
#include <stdio.h>
#include <string.h>
#include "../inc/complex_vector.h"
#include "../inc/cprivateTypes.h"

/* Functions */
vcomplex_t zInitEmpty() {
    /* Create a temporary empty struct */
    Vcomplex_t temp = EMPTY;

    /* Allocate memory for a pointer to the struct */
    vcomplex_t val = (Vcomplex_t*)malloc(sizeof(Vcomplex_t));

    /* Point the pointer to the empty temporary struct */
    *val = temp;

    /* Return the pointer to the struct */
    return val;
}
void pushz(vcomplex_t vector, complex_t value) {
    /* Determine if vector contains any values or not */
    if (vector->length == 0) {
        vector->vcomplex = (complex_t*)calloc(1, sizeof(complex_t));
        *vector->vcomplex = value;
        vector->length = 1;
    }
    else {
        /* If it does, add the value to the end */
        vector->length++;
        vector->vcomplex = (complex_t*)realloc(vector->vcomplex, sizeof(complex_t)*vector->length);
        *(vector->vcomplex + vector->length - 1) = value;
    }
}
complex_t popz(vcomplex_t vector) {
    /* Declare return variable */
    complex_t val = {0, 0};

    /* Determine if vector contains any values */
    if (vector->length > 0) {
        vector->length--;
        val = *(vector->vcomplex + vector->length);
        vector->vcomplex = (complex_t*)realloc(vector->vcomplex, sizeof(complex_t)*vector->length);
    }
    return val;
}
void clearz(vcomplex_t vector) {
    /* Check if the length is already 0 */
    if (vector->length > 0) {
        /* Set length to 0 and deallocate memory */
        vector->length = 0;
        free(vector->vcomplex);
        vector->vcomplex = NULL;
        free(vector);
    }
    else if (vector->length == 0) {
        /* For this case, the pointer that is a member of the vcomplex_t struct has not been allocated,
        therefore, it does not need to freed. Only the pointer to the vector needs to be deallocated. */
        free(vector);
    }
}
complex_t getZ(vcomplex_t vector, int index) {
    /* Declare variables */
    complex_t val = {0, 0};

    /* Check if index is within the range of the vector */
    if (index >= 0 && index < vector->length) {
        val = *(vector->vcomplex + index);
    }
    return val;
}
void vPrintZ(vcomplex_t vector) {
    /* Check if vector contains data */
    if (vector->length > 0) {
        /* Print values seperated by commas */
        int i = 0;
        for (i = 0; i < vector->length - 1; i++) {
            printComplex(*(vector->vcomplex+i));
            printf(", ");
        }
        printComplex(*(vector->vcomplex+i));
    }
    else {
        /* Inform the user that the vector is empty */
        printf("Empty Vector\n");
    }
}
size_t zLength(vcomplex_t vector) {
    return vector->length;
}