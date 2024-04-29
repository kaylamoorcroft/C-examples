/* 
 * File:	program.c 
 * Author:	Kayla Moorcroft  
 * Date:	2024/04/03 - 2024/04/05
 * Version:	1.0 
 * Purpose:	Creating an array that can store mixed elements of ints, floats and strings
 *			The user can input their own values or they can use the default test array
 * Notes:	Made it so that user can decide size of their array since instructions didn't
 *			specify the size of the user created array
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 50

// new datatype to store either int, float or string
typedef union {
	int i;
	float f;
	char *s;
} dataT;
// keeping track of which datatype in union is being used
typedef enum {
	integer, real, string
} dataTypeT;
// struct with both union & enum to easily work with different datatypes
typedef struct {
	dataTypeT tag;
	dataT value;
} taggedDataT;
// clear input till end of line - for readability in code 
void clearLine(void) {
	while(getchar() != '\n') 
			;
}
// print array with mixed elements of ints, floats and strings
void printArray(taggedDataT *array, int size) {
	for (int i = 0; i < size; i++) {
		int tag = array[i].tag;
		switch (tag) {
			case 0:	printf("%d\n", array[i].value.i);
					break;
			case 1:	printf("%f\n", array[i].value.f);
					break;
			case 2:	printf("%s\n", array[i].value.s);
		}
	}
}
// fill array by gathering user input of type of data to store and value of data
void fillUserArray(taggedDataT *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("\nData type: 1. integer, 2. real number, 3. string\n");
		int type = -1;
		while (type < 1 || type > 3) { // input validation
			printf("Enter 1, 2 or 3 > ");
			scanf("%d", &type);
			clearLine();
		}
		array[i].tag = type - 1; // tags are from 0 - 2
		switch (type) {
			case 1:	printf("Enter an integer number > ");
					scanf("%d", &array[i].value.i);
					break;
			case 2:	printf("Enter an real number > ");
					scanf("%f", &array[i].value.f);
					break;
			case 3: printf("Enter a string of no more than %d characters > ", MAX_STRING_LENGTH);
					if ((array[i].value.s = malloc(MAX_STRING_LENGTH*sizeof(char))) == NULL) {
						fprintf(stderr, "Error. Cannot allocate memory\n");
						exit(EXIT_FAILURE); 
					}
					fgets(array[i].value.s, MAX_STRING_LENGTH, stdin); // includes whitespace
					// get rid of \n char at end from fgets()
					for (int j = 0; j < MAX_STRING_LENGTH; j++) {
						if (array[i].value.s[j] == '\n') {
							array[i].value.s[j] = '\0';
							break;
						}
					}
			}
		}
}
// hardcodes size number of items into the array
// note: Instructions say 10 items, but wanted to make this variable so can be changed if needed
taggedDataT *hardCodeArray(int size) {
	taggedDataT *array;
	if ((array = malloc(size * sizeof(taggedDataT))) == NULL) {
		return array; // return NULL so can catch error in main()
	}
	for (int i = 0; i < size; i++) {
		int choice = i%3; // want to alternate between datatypes
		switch (choice) {
			case 0:	array[i].tag = integer;
					array[i].value.i = (rand()%10)*i; // random number between 0 & i*10
					// pseudorandom because same each run - doesn't matter because just want to fill array
					break;
			case 1:	array[i].tag = real;
					array[i].value.f = (rand()%10)/1.1234*i; // between 0 & i*11.234
					break;
			case 2:	array[i].tag = string; 
					if ((array[i].value.s = malloc(MAX_STRING_LENGTH*sizeof(char))) == NULL) {
						fprintf(stderr, "Error. Cannot allocate memory\n");
						exit(EXIT_FAILURE); // allocate memory so can use sprintf
					}
					sprintf(array[i].value.s, "string %d", i/3 + 1);
		}
	}
	return array;
}
// Deallocate memory for array: both the array and any strings
void clearArray(taggedDataT **array, int size) {
	// traverse array and deallocate all strings
    for (int i = 0; i < size; i++) {
		if((*array)[i].tag == string) {
			free((*array)[i].value.s);
			(*array)[i].value.s = NULL;
		}
    } // free actual array (pointer)
    free(*array);
    *array = NULL;
}
int main(void) {
	taggedDataT *array; 
	int size = 0;
	printf("Do you want to enter your own information for the array? ('y'es / 'n'o) > ");
	int option = getchar();
	clearLine();
	// if/else instead of switch because only 2 options
	if (option == 'y' || option == 'Y') { // doing this instead of include ctype.h and using tolower()
		while (size <= 0) { // input validation - size needs to be non-zero positive integer
			printf("Size of array (enter a positive value) > ");
			scanf("%d", &size);
			clearLine();
		}
		if ((array = malloc(size * sizeof(taggedDataT))) == NULL) {
			fprintf(stderr, "Error. Cannot allocate memory\n");
			return EXIT_FAILURE;
		}
		printf("\nNow let's add some elements...\n");
		fillUserArray(array, size); // get input and fill array
	}
	else { // entering anything besides 'y'
		size = 10;
		array = hardCodeArray(size); // fill array with predetermined values
		if (array == NULL) {
			fprintf(stderr, "Error. Cannot allocate memory\n");
			return EXIT_FAILURE;
		}
	}
	printf("\nHere is the array:\n");
	printArray(array, size); 
	clearArray(&array, size); // deallocate memory
	return EXIT_SUCCESS;
}
