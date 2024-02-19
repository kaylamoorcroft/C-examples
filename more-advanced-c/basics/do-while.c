/* 
 * File:    do-while.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/01/27 
 * Version: 1.0 
 * Pupose:  A number guessing game. Repeatedly asks the user for input until 
 * 			they guess the correct number. The "secret" number is a randomly 
 * 			generated number between 0-99 (inclusive). The user gets a hint
 * 			after each guess to get closer to the correct number.   
 * Notes:   We learned about generating random numbers in C in my
 * 			engineering programming class (APSC 1413)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used to create a seed for random generator

int main(void) {
    int user_num; // input num
	int secret_num; // num to guess
	srand(time(NULL)); // creating a seed for the random generator based on time
					   // so that each time the program is run, the secret
					   // number is different 
	secret_num = rand() % 100; // generating a num from 0-99 inclusive
	
	// explaining the program to the user
	printf("I'm thinking of a (integer) number between 0 and 99" 
			" (inclusive). Can you guess what it is...?\n");
	do {
		// taking user input (the guess)
		printf("Your guess > ");
		scanf("%d", &user_num);

		// giving the user hints based on their guess 
		if (user_num < 0 || user_num > 99) { // guess out of bounds
			printf("I said it was in between 0 and 99 (inclusive)...\n");
		} else if (secret_num < user_num) { // guess too high
			printf("Lower!\n");
		} else if (secret_num > user_num) { // guess too low
			printf("Higher!\n");
		}
	} while (user_num != secret_num); // loop until the number is guessed
	
	// the user finally guessed the number
	printf("You got it!! The secret number was %d\n",user_num);
    return EXIT_SUCCESS;
}
