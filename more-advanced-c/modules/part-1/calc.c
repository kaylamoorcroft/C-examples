/*
 * File:    calc.c
 * Author:	Kayla Moorcroft 
 * Date:    2024/02/14
 * Version: 1.0
 * Purpose:
 *         	A calulator that takes 2 numbers from the user and performs the
 *         	requested operation on them. There are 3 options:
 *         	> power: x^y
 *         	> bottom: floor(x/y) = floor of diving the 2 numbers
 *         	> rounded: round(x/y) = rounding the quotient of the 2 numbers 
 * Notes:   All the functions are included in this file for this part, so it's
 * 			self-contained without needed to compile with a different module
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // math module used to create math functions used in the calc

/* defining functions used in the program */
// gets a number from the user and returns it
int getNumber(void) {
	int num;
	scanf("%d", &num);
	while(getchar() != '\n') // clear till EOL to get rid of \n character
		;
	return num;
}
// gets an operator (char) from the user and returns it
int getOperator(void) {
	int letter = getchar();
//  scanf(" %c", &letter); // space in string gets rid of newline character
	while(getchar() != '\n') // clear till EOL
		;
	return letter;
}
// raises x to the power of y (x^y)
int power(int x, int y) {
	return pow(x, y);
}
// returns the nearest integer <= the floating point number of x / y
int bottom(int x, int y) {
	return floor((double)x/y);
}
// returns the closes integer to x / y (either larger or smaller)
int rounded(int x, int y) {
	return round((double)x/y);
}
/* the actual calculator program */
int main(void) {
	int x, y, operation;
	
	do {
		// get 2 numbers from the user
		printf("\nEnter a number > ");
		x = getNumber();
		printf("Enter another number > ");	
		y = getNumber();
		
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
