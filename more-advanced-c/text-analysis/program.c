/* 
 * File:    a5.c 
 * Author:  Kayla Moorcroft 
 * Date:    2024/03/08 -> 2024/03/13
 * Version: 1.0 
 * Purpose: Text analysis tool that performs various operations on text file
 *          --- FUNCTIONS ---
 *			1. Word/Character/Punctuation Count
 *			2. Substring Search
 *			3. Palindromic Words
 *			4. Encrypt a File
 *			5. Decrypt a File
 * Notes:   Functions are implemented in textAnalysis.c to make this file shorter
 *			Sample input file included in directory: "input.txt"
 *			Expected output included in separate file for each function
 *			"make clean" also removes encryption & decryption files
 */
#include <stdio.h>
#include <stdlib.h>
#include "textAnalysis.h"

extern char *filename; // global variable that textAnalysis.c uses.

// allocate space for any #items of any data type - 2024/03/13
void *allocate(int num, size_t size) { // simplifies writing code in main()
    void *mem;
    if ((mem = malloc(num * size)) == NULL) { //idiom
		fprintf(stderr, "Memory allocation failed...\n");
        exit(EXIT_FAILURE);
	}
    return mem;
}
// clear input till end of line - for readability in code - 2024/03/13
void clearLine(void) {
	while(getchar() != '\n') 
			;
}
int main(int argc, char *argv[]) {
	FILE *file = NULL, *encrypted = NULL;
	int encryptionKey = 0;
	if (argc != 2) { // if user not run program correctly
		printf("Usage: a5 <filename>\n");
		return EXIT_FAILURE;
	}
	filename = argv[1];
	file = openFile(file, filename, "r");
	while(1) { // infinite loop and only breaking out of it when user types 'q'
		printf("--- Choose a text analysis option ---\n"
		"1. Word/Character/Punctuation Count \n2. Substring Search \n"
		"3. Find Palindromic Words \n4. Encrypt File \n5. Decrypt File\n"
		"Enter 1/2/3/4/5 or enter 'q'uit to stop the program \n > ");
    	int option = getchar(); // getting user input
		clearLine();
		putchar('\n'); // just formatting
		// calling functions based on user input for option
		switch(option) {
			case '1':	printf("-----\nFile info:\n-----\n"); 
						countInfo(file);
						break;
			case '2':	printf("Enter a substring to search (max 50 chars) \n > ");
						char *substring = allocate(50, sizeof(char));
						scanf("%s", substring);
						clearLine();
						printf("\n-----\nOccurences of \"%s\" in file:\n-----\n", substring);
						findSubstring(file, substring);
						break;
			case '3':	printf("-----\nPalindromes in file:\n-----\n");
						findPalindromes(file); 
						break;
			case '4':	printf("-----\nEncryption:\n-----\n");
						printf("Enter encryption key (eg. \"5\") \n > ");
						scanf("%d", &encryptionKey);
						clearLine();
						encrypted = encrypt(file, encryptionKey);
						printf("New encrypted file \"%s.caesar\" created\n", filename);
						break;
			case '5':	printf("-----\nDecryption:\n-----\n");
						printf("Enter encryption key (eg. \"5\") \n > ");
						scanf("%d", &encryptionKey);
						clearLine();
						// create reference for encrypted file pointer if not exist
						char *encryptedFilename = mergeString(filename, ".caesar", 50);
						encrypted = openFile(encrypted, encryptedFilename, "r");
						decrypt(encrypted, encryptionKey);
						printf("New decrypted file \"%s.decrypted\" created\n", filename);
						break;
			case 'q':	
			case 'Q':	printf("Goodbye.\n"); // quit program
						closeFile(file, filename);
						return EXIT_SUCCESS;
			default:	printf("Invalid input... try again\n"); 
		}
		printf("-----\n\n");
	}
}
