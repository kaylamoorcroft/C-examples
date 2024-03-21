/* 
 * File:    textAnalysis.c 
 * Author:  Kayla Moorcroft  
 * Date:    2024/03/08 -> 2024/03/13
 * Version: 1.0 
 * Purpose: Functions for text analysis tool
 *          --- FUNCTIONS ---
 *			1. Word/Character/Punctuation Count
 *			2. Substring Search
 *			3. Palindromic Words
 *			4. Encrypt a File
 *			5. Decrypt a File
 * Notes:   Contains some private functions to make code more readable / modular
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
// doesn't include \0 at end:
#define MAX_LINE_LENGTH 256 
#define MAX_WORD_LENGTH 100

char *filename; // global variable so that can access in multiple functions

// allocate memory easier & initialise with calloc - private function
void *createEmptyMem(int num, size_t size) {
    void *mem;
    if ((mem = calloc(num, size)) == NULL) { //idiom
		fprintf(stderr, "Memory allocation failed...\n");
        exit(EXIT_FAILURE);
	}
    return mem;
}
// easy catenation without modifying either string - creates new str of size length
char *mergeString(const char *str1, const char *str2, int length) {
	char *merged = malloc(length*sizeof(char));
	strcpy(merged, str1); // no need to put \0 at end because cat adds \0
	return strcat(merged, str2);
}
// opening a file with a specific mode with error checking
FILE *openFile(FILE *file, const char *filename, const char *permissions) {
	if ((file = fopen(filename, permissions)) == NULL) {
		fprintf(stderr, "Cannot open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	return file;
}
// closing a file with error checking
void closeFile(FILE *file, const char *filename) {
	if (fclose(file) == EOF) {
		fprintf(stderr, "Cannot close file %s\n", filename);
		exit(EXIT_FAILURE);
	}
}
// Counts & prints out number of words, characters and punctuation in text file
// Words are defined as sequences of characters separated by spaces. 
void countInfo(FILE *file) {
	int c; // character we're reading
	int charCount = 0, wordCount = 0, punctCount = 0;
	while((c = fgetc(file)) != EOF) {
		if (isprint(c)) { charCount++; } // don't count ctr chars like \n
		if (ispunct(c)) { punctCount++; }
		if (isspace(c)) { wordCount++; }
	}
	rewind(file); // rewind cursor to start of file so can read again in other functions
	printf("Chars: %d\nWords: %d\nPunctuation: %d\n", charCount, wordCount, punctCount);
}
// Searches for all occurrences of substring in file
// If occurrence found, prints out line with substring in quotes
void findSubstring(FILE *file, const char *substring) {
	char *line = createEmptyMem(MAX_LINE_LENGTH + 1, sizeof(char)); 
	while(fgets(line, MAX_LINE_LENGTH + 1, file) != NULL) { // nothing was read / error
		char *restOfLine = line; // don't want to modify original pointer
		char *result = strcasestr(line, substring); // start of substring till EOL
		if (result == NULL) { continue; } // if no substring, next line
		while (result != NULL) { // if substring is in line, print line with substr in ""
			int startIndex = strlen(restOfLine) - strlen(result); 
			int endIndex = startIndex + strlen(substring);
			for (int i = 0; i < endIndex + 1; i++) {
			// determine if need quote at index but print whole line normally otherwise
				if (i == startIndex || i == endIndex) { putchar('"'); }
				putchar(restOfLine[i]);
			}
			restOfLine = restOfLine + endIndex + 1; // set rest of line
			result = strcasestr(restOfLine, substring); // another occurence in line?
		}
		printf("%s", restOfLine); // part after last substring
	}
	free(line); // need to manage own memory!
	line = NULL;
	rewind(file); // rewinding cursor back to beginning
}
// Finds and displays a list of palindromic words in file (1-letter words excluded)
void findPalindromes(FILE *file) {
	char *word = createEmptyMem(MAX_WORD_LENGTH + 1, sizeof(char));
	while (fscanf(file, "%s", word) != EOF) { // read word by word till EOF
		int size = strlen(word); // just for simplification
		int palindrome = 1; // assume true then have to prove otherwise
		for (int i = 0; i < size; i++) {
			if (!isalpha(word[i])) { // remove char if not letter
				for (int j = i; j < size; j++) {
					word[j] = word[j + 1]; // shift all chars 1 space left
				} // also copies over NULL character to new end of string
				size--; // word is now 1 letter shorter
				i--; // don't increment i in loop since deleted current char;
			}
		}
		if (size <= 1) { continue; } // 1-letter word is not palindrome
		for (int i = 0; i < size; i++) {
			if (tolower(word[i]) != tolower(word[size - i - 1])) {
				palindrome = 0;
				break;
			} // not palindrome - next word
		}
		if (palindrome != 0) { // anything except 0 is true
			printf("%s\n", word); // if word is palindrome, print out
		}
	}
	rewind(file);
}
// Private function to read text from a file & encrypt to new file
// Written generically for positive / negative offset
// Is called by encrypt() and decrypt() functions for more specific implementation
FILE *encryptToFile(FILE *file, int offset, const char *fileToCreate) {
	FILE *output = NULL; 
	output = openFile(output, fileToCreate, "w+"); // encrypted file
	int c; // character we're reading
	while((c = fgetc(file)) != EOF) { // read whole file char by char
		if (isprint((signed char)c)) { // only encrypt printable chars
			int offset_actual = offset; // keep original value for reference
			int sign = offset > 0 ? 1 : -1; // set sign based on +/- offset
			// find "actual offset", ie. skip over non-printable chars
			// generic loop to work regardless of positive / negative offset
			for (int i = 1*sign; abs(i) <= abs(offset_actual); i += 1*sign) {
				if (!isprint((signed char)(c+i))) { // cast as char to wrap around
					offset_actual += 1*sign; // increment / decrement if skip char
				}
			}
			fputc(c + offset_actual, output);
		} else { fputc(c, output); }// retain non-printable chars like \n
	}
	rewind(output);
	rewind(file);
	closeFile(output, fileToCreate); // close file after done with it
	return output;
}
// Encrypts a file using a caesar cypher with encryption key "offset"
// Creates new file <originalFilename.caesar>
// assume user has file that reading from open already because perform file operation on it
FILE *encrypt(FILE *file, int offset) {
	char *newFilename = mergeString(filename, ".caesar", 50);
	return encryptToFile(file, offset, newFilename);
}
// Decrypts a file using a caesar cypher with encryption key "offset"
// Essentially "encrypting" encrypted file by negative offset
// Creates new file <originalFilename.decrypted>
FILE *decrypt(FILE *file, int offset) {
	FILE *decrypted;
	char *newFilename = mergeString(filename, ".decrypted", 50);
	char *encryptedFilename = mergeString(filename, ".caesar", 50);
	openFile(file, encryptedFilename, "r");
	// decryption is encryption with the opposite offset it was encrypted with
	decrypted = encryptToFile(file, -offset, newFilename);
	closeFile(file, encryptedFilename);
	return decrypted;
}
