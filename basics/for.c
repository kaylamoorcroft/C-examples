/* 
 * File:    for.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/01/27 
 * Version: 1.0 
 * Pupose:	Creates a "slanted" pyramid / triangle based on the width input from
 * 			the user. The maximum width is 80 characters.
 * Notes:	I wanted to make the pyramid "centered", ie. the peak is in the
 * 			middle of the base, not slanted to the left. However, this required
 * 			more for loops. Also, the way that I was doing it meant that each
 * 			row would print an uneven number of *'s and thus the input width had
 * 			to be uneven as well. While it was possible to do this, I felt that
 * 			made the program too complicated since the assignment was literally 
 * 			just to show that we know how a for loop works. I already have a
 * 			while loop in here for input validation and I didn't want to have to
 * 			do more input validation just to make a "pretty picture".    
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int width;

	// getting input from the user
	printf("Enter (integer) width of the base of your pyramid > ");
	scanf("%d", &width);

	// making sure user enters valid input -> [0,80]
	while (width < 0 || width > 80) {
		printf("Please enter a number between 0 and 80 (inclusive) > ");
    	scanf("%d", &width);
	} 
	
	printf("Here is your pyramid: \n");
	// using nested for loops to print out rows of pyramids based on the width
	for (int i = 0; i < width; i++) {
		for (int j = 0; j <= i; j++) { // loop i times (num of *'s in row)
			printf("*"); // print all the *'s in the row
		}
		printf("\n"); // go to new row
	}
    return EXIT_SUCCESS;
}
