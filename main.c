/* File: main.c
 * Author: Alex Sylvanus
 * Description: Tests the complex number library 
 * 
*/

/* Includes */
#include <stdio.h>
#include <string.h>
#include "complex_library.h"

/* Functions */
void testComplexLib();
void testComplexVectorLib();
complex_t inputComplexNumber(string_t input);

// Print functions
void printMenu();

// Boolean functions
bool isExpression(string_t exp);

/* Begin main function */
int main() {
    // Declare variables
    char userInput[100];
    string_t s;
    complexFunction_t fnc = initFunc(sInit("z*z-i"));
    complex_t cInput = {
        0.0,
        0.0
    };
    complex_t cOutput = compute(fnc, cInput);
    
    /* Print welcome message */
    printf("Welcome to the complex number test\n");
    
    // Loop until user enters 'exit'
    while (strcmp(userInput, "exit")) {
        // Get the input from the user
        printMenu();
        scanf("%s", userInput);
        s = sInit(userInput);

        // Check that user doesn't enter exit
        if (strcmp(userInput, "exit")) {
            // Check if the expression contained a z
            if (isExpression(s)) {
                fnc = initFunc(sCopy(s));
                cOutput = compute(fnc, cInput);
            }
            else if (sEquals(s, "display")) { // Check if user enters display
                printf("\nFunction: f(z) = %s\n", getStr(fnc.fstring));
                printf("Input: z = ");
                printComplexLine(cInput);
                printf("Output: f(");
                printComplex(cInput);
                printf(") = ");
                printComplexLine(cOutput);
                printf("\n");
            }
            else {
                cInput = inputComplexNumber(sCopy(s));
                cOutput = compute(fnc, cInput);
            }
        }

        // Clear the current string
        clear(&s);
    }

    // Test parse func
    vstring_t stack = parseFunction(sInit("z*(sin(5.8+i))/0.874-avg(z,pi*i)"));
    vPrintS(stack);
    clears(stack);

    // Test Compute function
    complexFunction_t f = initFunc(sInit("z*z+i"));
    complex_t Z = {
        3.7,
        -1.3
    };
    printComplexLine(Z);
    Z = compute(f, Z);
    printComplexLine(Z);

    /* Run Tests */
    //testComplexLib();
    //testComplexVectorLib();

    /* Print goodbye */
    printf("\nGoodbye!\n");
    
    return 0;
}

complex_t inputComplexNumber(string_t input) {
    // Declare variables
    complexFunction_t func = initFunc(input);
    complex_t Z = {
        0.0,
        0.0
    }; // This will be used as dummy input into the compute function

    // Evaluate expression
    Z = compute(func, Z);

    // Return the complex number
    return Z;
}

void printMenu() {
    // Display the options
    printf("Enter 'display' to show the current values.\n");
    printf("Enter a complex number to set the current value.\n");
    printf("Enter an expression to set the current expression.\n");
    printf("Use 'z' in expression.\n");
    printf("Enter 'exit' to leave the program.\n");
    printf("::: ");
}

bool isExpression(string_t exp) {
    // Declare variables
    bool ret = false;
    char c = '0';

    // Loop through string
    int i = 0;
    while(i < getLength(exp)) {
        // Check if the current character is 'z' and break when one is detected
        c = getC(exp, i);
        if (c == 'z') {
            ret = true;
            break;
        }
        else {
            i++;
        }
    }

    // Return the variable
    return ret;
}

void testComplexLib() {
    /* Define variables */
    complex_t Z1 = {
        1.787267,
        3.9265
    };
    complex_t Z2 = {
        2.85622,
        -6.265319
    };
    complex_t Z3 = {
        -4.62633,
        -1.94385
    };

    /* Print variables */
    printf("Z1 = ");
    printComplexLine(Z1);
    printf("Z2 = ");
    printComplexLine(Z2);
    printf("Z3 = ");
    printComplexLine(Z3);

    /* Perform operations and print operations on variables */
    printf("\nAddition: Z1 + Z2 = ");
    printComplexLine(cAdd(Z1, Z2));

    printf("\nSubtraction: Z2 - Z1 = ");
    printComplexLine(cSub(Z2, Z1));

    printf("\nMultiplication: Z1*Z3 = ");
    printComplexLine(cMul(Z1, Z3));

    printf("\nDivision: Z3/Z2 = ");
    printComplexLine(cDiv(Z3, Z2));
}

void testComplexVectorLib() {
    /* Define variables */
    complex_t Z1 = {
        1.787267,
        3.9265
    };
    complex_t Z2 = {
        2.85622,
        -6.265319
    };
    complex_t Z3 = {
        -4.62633,
        -1.94385
    };

    /* Inform user whats happening */
    printf("Creating complex vector. . .\n");
    vcomplex_t v = zInitEmpty();
    printf("Testing clearz on empty vector\n");
    clearz(v);
    printf("It worked!\n");
    v = zInitEmpty();

    /* Add values to vector */
    printf("Adding values to the vector. . .\n");
    pushz(v, Z1);
    pushz(v, Z2);
    pushz(v, Z3);
    pushz(v, cExp(Z2));
    pushz(v, cSin(Z1));
    pushz(v, cLn(Z2));
    pushz(v, cTan(Z3));
    printf("Values added.\nv = [");
    vPrintZ(v);
    printf("]\n");

    /* Test the pop and get functions */
    printf("\nTesting get utility: v[3] = ");
    printComplexLine(getZ(v, 3));
    printf("\nTesting pop utility. Last 3 values are:\n");
    int i = 0;
    for (i = 0; i < 3; i++) {
        Z1 = popz(v);
        printComplexLine(Z1);
    }
    printf("Vector is now: v = [");
    vPrintZ(v);
    printf("]\n");

    /* Clear the vector */
    printf("\nClearing vector. . .\n");
    clearz(v);
    printf("Success!\n");
}
