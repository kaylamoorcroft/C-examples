/* 
 * File:	a4.c 
 * Author:	Kayla Moorcroft 0301408m@acadiau.ca 
 * Date:   	2024/03/01 - 2024/03/05
 * Version:	1.0 
 * Purpose:	Creating an integer array using pointers and performing various
 * 		functions on the array:
 * 		printing, finding the max / min / sum / average values of the
 *		array. And there is a function to create the array (allocate
 * 		the memory) and to deallocate the memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used to create a seed for random generator

// Dynamically allocates memory for an array of integers
// Populates the array with random values between 1-100 (inclusively)
int* createArray(int size) {
	int *array;
	// allocating memory with error checking - size + 1 because want
	// to include "null terminator" to indicate end of array
	if ((array = malloc((size + 1) * sizeof(int))) == NULL) {
		return NULL;
	}
	// putting the rest of the code here because don't need to bother with 
	// random generation if memory allocation failed
	else { 
		srand(time(NULL));
		// using this seed generates new numbers with every run
		// populate array with rand values
		for (int i = 0; i < size; i++) {
			*(array + i) = rand() % 100 + 1;
			// using pointer arithmetic to access indices
			// generate random value between 1-100 (inclusively)
		}
		*(array + size) = 0; // used to indicate end of array
		return array;
	}
}
// prints out array
// takes in const int array as parameter to indicate that array won't be changed
void printArray(const int *array) {
	// different pointer because don't want to change base value of *array
	int* toPrint = (int*)array; 
	// print out slightly differently based on where in array currently are
	// because want to format properly
	if (*toPrint == 0) { // if empty array, just print brackets then exit
		printf("[]\n"); 
		return;
	}
	printf("[%d",*toPrint); // start of array if array not empty
	toPrint++;
	while(*toPrint != 0) { // while not at end of array
		printf(", %d", *toPrint); // middle of array
		toPrint++;
	}
	printf("]\n"); // end of array
}
// finding maximum value in array
int max(const int *array){
	int* num = (int*)array; // pointer to increment through array
	int max = *num;
	while(*num != 0) { // while not at end of array
		if (*num > max) { max = *num; } // new max
		num++;
	}
	return max;
}
// finding minimum value in array
int min(const int *array){
	int* num = (int*)array; // pointer to increment through array
	int min = *num;
	while(*num != 0) { // while not at end of array
		if (*num < min) { min = *num; } // new min
		num++; 
	}
	return min;
}
// computing sum of array elements
int sum(const int *array) {
	int* num = (int*)array; // pointer to increment through array
	int sum = 0;
	while(*num != 0) { // while not at end of array
		sum += *num; // add current element to sum
		num++; 
	}
	return sum;
}
// computing average of array elements
float average(const int *array) {
	/*int sumCalc = sum(array);
	return (float)sumCalc/size;*/
	// ^ Could do this and use size as param, but don't trust user, so will
	// increment through array myself and count # elements
	// So some code copied from sum function
	int* num = (int*)array; // pointer to increment through array
	int sum = 0;
	int numElements = 0;
	if (*num == 0) {return 0;} // empty array
	// don't want to cause divide by 0 error when divide by 0 elements
	while(*num != 0) { // while not at end of array
		sum += *num; // add current element to sum
		num++; 
		numElements++; // count num elements to find average
	}
	return (float)sum/numElements; // return ave
}
// Reversing the array in place using pointer manipulation
// Modifies the array that is passed in
void reverse(int* array){
	int* num = array; 
	// to count # elements because don't want to change reference of *array
	int size = 0;
	// count num elements in array, excluding 0
	while(*num != 0) { 
		size++;
		num++; // next element
	}
	// reverse array - only go till middle since swapping elements
	// size/2 truncates odd values of size so don't "swap" middle value
	// since it has to stay the same anyway.
	for (int i = 0; i < size/2; i++) {
		int hold = *(array + size - (i + 1)); 
		// element at current index from end of array
		*(array + size - (i + 1)) = *(array + i); 
		*(array + i) = hold;
		// element i becomes element size - i - 1 and vice versa
	}
}
// deallocates the memory used by the dynamically allocated array
// need to pass in pointer to pointer (change address of pointer)
void deallocate(int **memory) {
	free(*memory);
	*memory = NULL;
}
int main(void) {
	int* array; 
	int size;
	// creating array based on user size input
	printf("Please enter the size of the array: ");
	scanf("%d", &size);
	if((array = createArray(size)) == NULL) { // have same idiom here
		printf("Not enough memory available to create array of this "
		"size. Ending program...\n"); // telling user what's happening
		return EXIT_FAILURE;
	}
	// calling the functions created as per the instructions and explain to user
	printf("\nThis is your array with \"randomly\" populated integers:\n");
	printArray(array);
	printf("\nMax value in array: %d\n", max(array));
	printf("Min value in array: %d\n", min(array));
	printf("\nSum of values in array: %d\n", sum(array));
	printf("Average of values in array: %.2f\n", average(array));
	printf("\nReversing the array results in: \n");
	reverse(array);
	printArray(array);
	deallocate(&array); // deallocate memory that was allocated in beginning
	return EXIT_SUCCESS;
}
