/* 
 * File:    switch.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/01/27 
 * Version: 1.0 
 * Pupose:	Simulates a journal / diary. Prompts the user for an entry on how
 * 			they are feeling. Depending on the answer, prints out an emoticon
 * 			corresponding to their emotion. The program takes multiple entries
 * 			and ends when the user types 'q'.  
 * Notes:	   
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int letter; // declare as int because getchar() returns an int
	// explaining the program to the user
	printf("-- Welcome to your journal -- \n");
	printf("Type 'q'uit to stop making more entries\n\n");
	
	// infinite loop and only breaking out of it when user types 'q'
	// loop allows multiple entries
	while(1) {
		// getting user input
		printf("How are you feeling today? ('s'ad, 'h'appy, 'a'ngry, 'b'ored"
			", an'x'ious) > ");
    	letter = getchar();

		while(getchar() != '\n') // clear till end of line
			;
		
		// printing out different things based on user input
		switch(letter) {
			case 'a':
			case 'A':	printf(">:(\n");
						break;
			case 'b':
			case 'B':	printf("-_-\n");
						break;
			case 'h':	
			case 'H':	printf(":)\n");
						break;
			case 's':	
			case 'S':	printf(":(\n");
						break;
			case 'x':
			case 'X':	printf(">:O\n");
						break;
			case 'q':	
			case 'Q':	printf("Goodbye.\n"); // quit program
						return EXIT_SUCCESS;
			default:	printf("Invalid input... try again\n"); 
		}
	}
}
