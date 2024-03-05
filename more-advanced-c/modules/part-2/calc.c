/*
 * File:    calc.c
 * Author:  Kayla Moorcroft 
 * Date:    2024/02/14
 * Version: 1.0
 * Purpose:
 *			A calulator that takes 2 numbers from the user and performs the
 *			requested operation on them. There are 3 options:
 *   		> power: x^y
 *     		> bottom: floor(x/y) = floor of diving the 2 numbers
 *    		> rounded: round(x/y) = rounding the quotient of the 2 numbers
 * Notes:	The math functions used in the calculator are defined in a different 
 * 			module that gets included during compilation with the makefile.  
 */

#include <stdio.h>
#include <stdlib.h>
#include "myMath.h" // module with functions used in the calculator

int main(void) {
	int x, y, operation;

	do {
		// get 2 numbers from the user
		printf("\nEnter a number > ");
		x = getNumber();
		printf("Enter another number > ");	
		y = getNumber();
		
		// get the operation to perform on the 2 numbers
		printf("\nSelect an operation ('p'ower, 'f'loor, 'r'ound, 'e'xit) > ");
		operation = getOperator();

		switch (operation) { // perform operation based on the input
							 // fallthrough cases included to be case insensitive
			// power: x^y
			case 'p':
			case 'P':	printf("\n>> %d^%d = %d\n", x, y, power(x, y));
						break;
			// floor(x/y)
			case 'f':
			case 'F':	printf("\n>> floor(%d/%d) = %d\n", x, y, bottom(x, y));
						break;
			// round(x/y)
			case 'r':
			case 'R':	printf("\n>> round(%d/%d) = %d\n", x, y, rounded(x, y));
						break;
			// exit program
			case 'e':
			case 'E':	printf("\n>> Okay, I guess we are done. Goodbye.\n\n");
						return EXIT_SUCCESS;
			// invalid input
			default:	printf("\n>> Invalid operation. Please try again...\n");
		}
	} while(1); // infinite loop to break in middle when user enters 'e'
}
