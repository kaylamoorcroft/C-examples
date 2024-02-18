/* 
 * File:    while.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/01/27 
 * Version: 1.0 
 * Pupose:	Computes the area of a square based on the side length given by the
 * 			user.   
 * Notes:	The maximum length of a side is 10m for this program in order to 
 * 			demonstrate the use of a while loop to check for input validation
 * 			(values larger than 10 or negative values are invalid)   
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // get length of side of square from user
	double sideLength;
	printf("Enter the length of one side of the square (in metres) > ");
	scanf("%lf", &sideLength);
	
	// if the input is invalid, keep prompting the user for a new value until 
	// they enter a valid number
	while (sideLength < 0 || sideLength > 10) {
		// specific messages to tell the user why their input is invalid
		if (sideLength < 0) {
			printf("Please enter a non-negative number > ");
		} else if (sideLength > 10) {
			printf("\tSorry, the maximum side length that I'm able to compute"
					" is 10 metres. \nPlease enter a length less than 10 m > ");
		}
		// take input again
		scanf("%lf", &sideLength);
	}
	// print the resulting area of the square 
	printf("The area of your square is: %lf m^2\n", sideLength*sideLength);
    return EXIT_SUCCESS;
}

