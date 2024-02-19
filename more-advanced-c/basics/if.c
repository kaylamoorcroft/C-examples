/* 
 * File:    if.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/01/24 
 * Version: 1.0 
 * Pupose:	Reading in a number from the user and then telling them whether 
 * 			the number they entered is positive, negative or neutral (zero)  
 * Notes:   The input is taken as a double in case the user enters a 
 * 			floating point number and not an integer
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// getting user input - doesn't matter if int or double, just the sign (+/-)
	double user_num;
	printf("Please enter a number > ");
	scanf("%lf", &user_num);
	
	// using if statements to print out the sign corresponding the user's number
	if (user_num < 0) {
		printf("You entered a negative number\n");
	} else if (user_num > 0) {
		printf("You entered a positive number\n");
	} else {
		printf("You entered zero\n");
	}
	
	// ending program
	return EXIT_SUCCESS;
}
