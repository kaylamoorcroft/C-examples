/*
 * File:    text-alteration.c
 * Author:  Kayla Moorcroft  
 * Date:    2024/02/02 - 2024/02/05
 * Version: 1.0
 * Pupose:	Reads input and creates an output based on which task is run:
 *			Task 1 - "filter" - outputs exactly what is entered, character by
 * 			character
 * 			Task 2 - "switched" - swaps uppercase and lowercase letters - if 
 * 			uppercase, make lowercase, and if lowercase, make uppercase.
 * 			Task 3 - "reversed" - prints out the entire text backwards  
 * Notes:	A file can be redirected to be input, or the same can be done to output
 * 			to a file. So the input doesn't have to come from the command line.    
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // need for isupper() and tolower() functions etc.

int main(void) {
	int letter; // letter to be read in
	#ifdef REVERSED
	FILE *temp; // temp file to use in task 3
	temp = tmpfile(); // creating a temp file
	#endif
	while ((letter = getchar()) != EOF) { // idiom
		// do task 1 if other macros not defined - filter - input = output to screen
		#ifdef FILTER
		putchar(letter);
		#endif
		// task 2 - switch uppercase and lowercase and print to screen
		#ifdef SWITCHED
		if (isupper(letter)) {
			putchar(tolower(letter));
		} else if (islower(letter)) {
			putchar(toupper(letter));
		} else { // if not a letter but a different character instead
			putchar(letter);
		}
		#endif
		// task 3 - switch uppercase and lowercase but write to temp file not screen
		#ifdef REVERSED
		if (isupper(letter)) {
			fputc(tolower(letter), temp);
		} else if (islower(letter)) {
			fputc(toupper(letter), temp);
		} else { // if not a letter but a different character instead
			fputc(letter, temp);
		}
		#endif
	}	
	// display file backwards to screen for task 3
	#ifdef REVERSED
	// get first char before start "rewinding" by 2 chars	
	fseek(temp, -1, SEEK_END);
	putchar(fgetc(temp));
	while (ftell(temp) > 1) { // while not at start of file yet
		fseek(temp, -2, SEEK_CUR); // move 1 space (char) back in file - put char
								  // moves 1 forward, so have to move 2 back to 
								  // actually move 1 back (counteracting it)
		putchar(fgetc(temp)); // print current char in file to screen
		//printf("Index: %ld \n", ftell(temp));
	}
    #endif
    return EXIT_SUCCESS;
}
