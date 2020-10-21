/* File: complex_function.c
 * Author: Alex Sylvanus
 * Description: Declares the the struct for a complex_function
 * 
*/

/* Includes */
#include "../inc/complex_function.h"
#include <stdio.h>
#include <math.h>

/* Enumerated types */
typedef enum {
    OPENPAREN,
    LETTER,
    NUMERICAL,
    OPERATOR,
    CLOSEDPAREN,
    ERRORC
} charType_e;

typedef enum {
    EXP,
    LN,
    SIN,
    COS,
    TAN,
    NGTV,
    ABS,
    PHI,
    ERRORF
} unaryFunction_e;

typedef enum {
    AVG,
    ERRORB
} binaryFunction_e;

/* Structs */
typedef struct {
    unaryFunction_e fcode;
    const char* name;
    complex_t(*func)(complex_t);
} unaryFunction_t;

typedef struct {
    binaryFunction_e fcode;
    const char* name;
    complex_t(*func)(complex_t, complex_t);
} binaryFunction_t;

/* Unions */
typedef union {
    unaryFunction_t unary;
    binaryFunction_t binary;
} function_t;

/* ==== Private Functions ==== */
/* Character classification */
bool isWhitespace(char c) {
	return (c==' ' || c== '\n' || c=='\r' || c=='\t');
}
bool isLowercase(char c) {
	return (c>='a' && c<='z');
}
bool isUppercase(char c) {
	return (c>='A' && c<='Z');
}
bool isLetter(char c) {
	return (isUppercase(c) || isLowercase(c));
}
bool isNumerical(char c) {
	return ((c>='0' && c<='9') || c == '.');
}
bool isOperator(char c) {
	return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c==',');
}
charType_e labelChar(char c) {
    /* Declare return variable */
    charType_e ret = ERRORC;

    /* Classify */
    if (c == '(') {
        ret = OPENPAREN;
    }
    else if (isLetter(c)) {
        ret = LETTER;
    }
    else if (isNumerical(c)) {
        ret = NUMERICAL;
    }
    else if (isOperator(c)) {
        ret = OPERATOR;
    }
    else if (c == ')') {
        ret = CLOSEDPAREN;
    }
    return ret;
}

/* String classification */
bool isStringOperator(string_t s) {
    /* Check that string length is 1 */
    if (getLength(s) == 1) {
        /* Get the first index */
        char c = getC(s, 0);
        return isOperator(c);
    }
    else {
        return false;
    }
}
bool isStringConstant(string_t s) {
    /* Check if the string is one of the math constants or z */
    return (sEquals(s, "z") || sEquals(s, "e") || sEquals(s, "pi") || sEquals(s, "i"));
}
bool isStringUnary(string_t s) {
    /* Check if string is one of the following unary functions */
    if (
        sEquals(s, "exp") ||
        sEquals(s, "ln") ||
        sEquals(s, "sin") ||
        sEquals(s, "cos") ||
        sEquals(s, "tan") ||
        sEquals(s, "ngtv") || /* this is inserted by the code, not the user, typically */
        sEquals(s, "abs") ||
        sEquals(s,"phi")
    ) {
        return true;
    }
    else {
        return false;
    }
}
bool isStringBinary(string_t s) {
    /* Check if string is one of the following unary functions */
    if (
        sEquals(s, "avg") 
    ) {
        return true;
    }
    else {
        return false;
    }
}
binaryFunction_t labelBFunc(string_t s){    
    /* Declare return variable */
    binaryFunction_t f;

    if (isStringBinary(s)) {
        /* Classify string */
        if (sEquals(s, "avg")) {
            f.fcode = AVG;
            f.func = &cAvg;
        }
        
    }
    else {
        f.fcode = ERRORF;
        f.func = NULL;
    }
    f.name = getStr(s);
    return f;}
unaryFunction_t labelUFunc(string_t s) {
    /* Declare return variable */
    unaryFunction_t f;

    if (isStringUnary(s)) {
        /* Classify string */
        if (sEquals(s, "exp")) {
            f.fcode = EXP;
            f.func = &cExp;
        }
        else if(sEquals(s, "ln")) {
            f.fcode = LN;
            f.func = &cLn;
        }
        else if (sEquals(s, "sin")) {
            f.fcode = SIN;
            f.func = &cSin;
        }
        else if (sEquals(s, "cos")) {
            f.fcode = COS;
            f.func = &cCos;
        }
        else if (sEquals(s, "tan")) {
            f.fcode = TAN;
            f.func = &cTan;
        }
        else if (sEquals(s, "ngtv")) {
            f.fcode = NGTV;
            f.func = &cNgtv;
        }
        else if (sEquals(s, "abs")) {
            f.fcode = ABS;
            f.func = &cAbs;
        }
        else if (sEquals(s, "phi")) {
            f.fcode = PHI;
            f.func = &cPhi;
        }
    }
    else {
        f.fcode = ERRORF;
        f.func = NULL;
    }
    f.name = getStr(s);
    return f;
}

function_t labelFunc(string_t s) {
    function_t f;
    if (isStringBinary(s)) {
        f.binary = labelBFunc(s);
    }
    else if (isStringUnary(s)) {
        f.unary = labelUFunc(s);
    }
    return f;
}

/* Operator classification */
int priority(string_t s) {
    /* Set the priority for the order of operations as an int */
    if (sEquals(s, "^")) {
        return 5;
    }
    else if (sEquals(s, "ngtv")) { /* Polarizing a number takes priority over multiplication */
        return 4;
    }
    else if (sEquals(s, "*") || sEquals(s, "/")) {
        return 3;
    }
    else if (sEquals(s, "+") || sEquals(s, "-")) {
        return 2;
    }
    else if (sEquals(s, ",")) {
        return 1;
    }
    else {
        return 0;
    }
}

/* Computation */
complex_t computeUnary(complex_t z, string_t s) {
    /* Declare return variable */
    complex_t Z = {0, 0};

    unaryFunction_t f = labelUFunc(s);
    /* Check if function was successfully returned */
    if (f.func != NULL) {
        return (f.func)(z);
    }
    else {
        return Z;
    }
}
complex_t computeBinary(complex_t z1, complex_t z2, string_t s) {
    // Declare return variable
    complex_t ret = {0, 0};

    /* Declare temp binary function */
    binaryFunction_t f;

    /* Check which operator was passed */
    if (isStringOperator(s)) {
        if (sEquals(s, "+")) {
            return cAdd(z1, z2);
        }
        else if (sEquals(s, "-")) {
            return cSub(z1, z2);
        }
        else if (sEquals(s, "*")) {
            return cMul(z1, z2);
        }
        else if (sEquals(s, "/")) {
            return cDiv(z1, z2);
        }
        else if (sEquals(s, "^")) {
            return cPow(z1, z2);
        }
    }
    else if (isStringBinary(s)) {
        f = labelBFunc(s);
        /* Check if function was successfully returned */
        if (f.func != NULL) {
            return (f.func)(z1, z2);
        }
    }
    else {
        return ret;
    }
}

/* ==== Public Functions ==== */
vstring_t parseFunction(string_t s) {
    /* Declare flags for processing strings or numbers */
    bool num = false;
    bool str = false;

    /* Declare temporary variables */
    char c = getC(s, 0);
    charType_e cl = labelChar(c);
    int order = 0;
    string_t str_temp = sInit(""); // Memory allocated
    string_t op_temp = sInit(""); // Memory allocated
    vstring_t ops = vInitS_Blank(); // Memory allocated
    vstring_t parsed = vInitS_Blank(); // Memory allocated

    /* Attempt to fix string: @TODO */

    /* Loop through the string */
    int i = 0;
    for (i = 0; i < getLength(s); i++) {
        /* Label the current character */
        c = getC(s, i); // This will be the current character
        cl = labelChar(c);
        //printf("%c\n", c);

        /* Set point for character analysis to reduce options checked in the nested if statements */
        switch(cl) {
            case OPENPAREN:
                // printf("Open parentheses\n");
                /* Open paren code goes here */
                if (str) {  /* function from context */
					str = false; /* Open parentheses should mark the end of a string, therefore
                    set the check variable to false */
					if (isStringUnary(str_temp)) {
                        /* Store the unary function in the operator stack */
						pushString(ops, "("); 
						pushs_c(ops, &str_temp); /* pushs frees the input string, so we do not need to clear str_temp */


						// str_temp = sInit("(");
						break;
					}
                    if (isStringBinary(str_temp)) {
                        pushString(ops, "(");
                        //pushString(ops, "("); /* Add an extra parentheses that will get resolved by the comma */
                        pushs_c(ops, &str_temp);

                        break;
                    }
					else { 
						printf("%s is not a valid function preceding (. Invalid format\n", str_temp);
						exit(0);
					}
				}
				if (num) { // if previously processing a number, an open parentheses will generate an error
					printf("Number next to (. Invalid format\n");
					exit(0);
				}
				pushString(ops, "(");
				clear(&str_temp);
                break;


            case LETTER:
                // printf("Letter\n");
                /* Letter code goes here */
                if (num) {
					printf("Not expecting letter after number. Invalid format.\n");
					exit(0);
				}
                if (str) {
					append(str_temp, c);
					break;
				}
				
                str_temp = sInit("");
                append(str_temp, c);
				num = false;
				str = true;
                break;

            case NUMERICAL:
                // printf("Numerical\n");
                /* Numerical code goes here */
                if (num) {
					append(str_temp, c);
					break;
				}
				if (str) {
					printf("Not expecting number after letter. Invalid format\n");
					exit(0);
				}
                str_temp = sInit("");
				append(str_temp, c);
				str = false;
				num = true;
                break;

            case OPERATOR:
                // printf("Operator\n");
                /* OOoo boy, here comes a lot of code */
                if (i==0 || (!str && !num && getC(s, i-1) != ')')) {
					/* The first char in the string or no num and str flags and the previous
					 char is not a closeparen */
					if ( i>1 && labelChar(getC(s, i-1))==OPERATOR && labelChar(getC(s, i-2))==OPERATOR) {
						// If greater than the second index, the two prior indexes
						// are operators, throw exception
						printf("Too many operators in a row. Invalid format\n");
						exit(0);
					}
					
					// Break if current char is a plus sign
					if (c=='+') {
						break;
					}
					
					// Decide what to do with minus sign
					if (c=='-') {
						// Get the priority from ngtv, should be 3
                        if (getLength(str_temp) > 0) {
                            clear(&str_temp);
                        }
						str_temp = sInit("ngtv");
						order = priority(str_temp);
						
						// Check if operator stack is empty
						if (getLengthS(ops) > 0) {
							// Copy operator stack to parsed stack until empty, or if the priority is less
							while (getLengthS(ops) > 0) {
								op_temp = pops(ops);
								if (priority(op_temp)>=order) {
									pushs_c(parsed, &op_temp);
								}
								else { // Break the loop if the priority of the temporary operator is greater
									pushs_c(ops, &op_temp);
									break; // while loop
								}
							}
						}
						pushs_c(ops, &str_temp); // str_temp cleared
						break;
					}
					exit(0);
				}
				// If currently processing string
				if (str) {  // variable or constant from context
					if (isStringConstant(str_temp)) {
						pushs_c(parsed, &str_temp); // str_temp cleared
					}
					else {
						exit(0);
					}
				}
				// Add currently processed number
				if (num) {
					pushs_c(parsed, &str_temp);
				}
				
                /* See if operator is comma */
                
				// Reset str and num flags
				str = false;
				num = false;
				
				// Set the temp string equal to the current operator
                if (getLength(str_temp) > 0) {
                    clear(&str_temp);
                }
                
                str_temp = sInit("");
				append(str_temp, c);

				// Update the operator stack according to priority
				order = priority(str_temp);
				if (getLengthS(ops) > 0) { // Check if stack is empty
					while (getLengthS(ops) > 0) { // While it's not empty, copy operators to parsed stack
						op_temp = pops(ops);
						if (priority(op_temp)>=order) {
							pushs_c(parsed, &op_temp); /* op_temp gets cleared here */
						}
						else { // If the priority of the current operator is higher, stop copying
							pushs_c(ops, &op_temp);
							break; // while loop
						}
					}
				}
                // Perform action for closed parentheses
				pushs_c(ops, &str_temp);
                // printf("Reached this point\n");
                break;

            case CLOSEDPAREN:
                /* Detect error when string begins with closed parentheses */
                if (!str && !num && !(i>0 && getC(s, i-1)==')')) {
					exit(0);
				}
				// If a number is being processed, push it to the parsed stack
				if (num) {
					pushs_c(parsed, &str_temp); /* str_temp gets cleared here */
				}
				
				// If a string is being processed, check that it's a valid string
				if (str) {  // variable or constant from context
					if (isStringConstant(str_temp)) {
						pushs_c(parsed, &str_temp);
					}
				}
				
				// Reset number and string flags
				num = false;
				str = false;
				
				// Copy the operator list until a ( is detected.
				// This ensures that the math inside the parentheses is prioritized 
				while (getLengthS(ops) > 0) {
					op_temp = pops(ops);
					if (!sEquals(op_temp, "(")) {
						pushs_c(parsed, &op_temp);
					}
					else {
						break; // Go back to beginning
					}
				}
				break;

            case ERRORC:
                /* Invalid character */
                exit(0);
        }
        /*
        if (getLength(str_temp) > 0) {
            printf("%s\n", getStr(str_temp));
        }*/
        // vPrintS(ops);
        // vPrintS(parsed);
        
    }
    // printf("Loop finished\n");
    /* Clean up after string loop finishes */
    if (str) {
        if (isStringConstant(str_temp)) {
            pushs_c(parsed, &str_temp);
        }
        else {
            exit(0);
        }
    }
    
    /* Add currently processed number */
    if (num) {
        pushs_c(parsed, &str_temp);
    }

    /* Clear the operator stack */
    while (getLengthS(ops) > 0) {
        op_temp = pops(ops);
        if (!sEquals(op_temp, "(")) {
            pushs_c(parsed, &op_temp);
        }
        else {
            exit(0);
        }
    }

    // printf("Cleared op stack\n");
    /* Clear vector */
    clears(ops);
    // vPrintS(parsed);
    /* Reverse the stack */
    vstring_t reversed = vInitS_Blank();
    while (getLengthS(parsed) > 0) {
        str_temp = pops(parsed);
        pushs_c(reversed, &str_temp);
    }
    clears(parsed);

    // Return the reversed stack
    return reversed;
}

complexFunction_t initFunc(string_t s) {
    // Declare variables
    vstring_t stack = parseFunction(s);
    complexFunction_t ret;

    // Assign values
    ret.fstring = s;
    ret.fstack = stack;

    // Return the struct
    return ret;
}

complex_t compute(complexFunction_t f, complex_t z) {
    // Declare local variables
    string_t str_curr;
    complex_t z1 = {0, 0};
    complex_t z2 = {0, 0};
    float fltemp = 0.0;

    // Declare stacks for computation
    /* Complex Stack complex_vals*/
    vcomplex_t complex_vals = zInitEmpty();
    vstring_t localstack = vInitS_Blank();

    // Copy contents from function stack into local stack
    int i = 0;
    for (i = 0; i < getLengthS(f.fstack); i++) {
        pushs(localstack, getS(f.fstack, i));
    }

    // Define constants for substitution
    complex_t e = {M_E, 0};
    complex_t pi = {M_PI, 0};
    complex_t j = {0, 1.0};

    // Loop while the stack is not empty
    while(getLengthS(localstack) > 0) {
        // Get the current string
        str_curr = pops(localstack);

        // Check what kind of operator
        if (isStringConstant(str_curr)) {
            if (sEquals(str_curr, "z")) {
                pushz(complex_vals, z);
            }
            else if (sEquals(str_curr, "e")) {
                pushz(complex_vals, e);
            }
            else if (sEquals(str_curr, "pi")) {
                pushz(complex_vals, pi);
            }
            else if (sEquals(str_curr, "i")) {
                pushz(complex_vals, j);
            }
        }
        else if (isStringUnary(str_curr)) {
            pushz(complex_vals, computeUnary(popz(complex_vals), str_curr));
        }
        else if (isStringOperator(str_curr)) {
            /* If its a comma pop and clear */
            if (sEquals(str_curr, ",")) {
                str_curr = pops(localstack);
            }
            z2 = popz(complex_vals);
            z1 = popz(complex_vals);
            pushz(complex_vals, computeBinary(z1, z2, str_curr));
        }
        else {
            fltemp = fStr(str_curr);
            z1.real = fltemp;
            z1.imaginary = 0;
            pushz(complex_vals, z1);
        }
    }
    z1 = popz(complex_vals);
    clearz(complex_vals);
    clears(localstack);

    // Return the final value
    return z1;
}