/*
 * File:    0301408mMath.c
 * Author:  Kayla Moorcroft 
 * Date:    2024/02/14
 * Version: 1.1
 * Purpose:
 * 			A library of functions to be used by another class. Ideal for building
 * 			a calculator
 * 			> getNumber: getting user input as a number
 * 			> getOperator: getting a character from the user that can be used to
 * 			determine which of the 3 math operations the class should perform
 * 			(power, bottom, or rounded)
 *          > power: x^y
 *          > bottom: floor(x/y) = floor of diving the 2 numbers
 *          > rounded: round(x/y) = rounding the quotient of the 2 numbers
 * Notes:	Changed function names to bottom and rounded instead of floorDiv and
 * 			roundDiv, respectively.   
 */

#include <stdio.h>
#include <math.h> // math module used to create math functions

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
//	scanf(" %c", &letter); // space in string gets rid of newline character
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
