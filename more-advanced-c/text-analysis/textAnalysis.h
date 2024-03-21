// -- Wed, Mar 13, Evening --

#ifndef TEXTANALYSIS_H
#define TEXTANALYSIS_H
// Max line length is 256 chars (excluding \0)
// Max word length is 100 chars (excluding \0)

// easy catenation without modifying either string - creates new str of size length
char *mergeString(const char *str1, const char *str2, int length);
// opening a file with a specific mode with error checking
FILE *openFile(FILE *file, const char *filename, const char *permissions);
// closing a file with error checking
void closeFile(FILE *file, const char *filename);
// Displays word/char/punctuation count of file
void countInfo(FILE *file);
// Finds and displays all occurences of substring in file
void findSubstring(FILE *file, const char *substring);
// Finds and displays a list of palindromic words in file (1-letter words excluded)
void findPalindromes(FILE *file);
// Encrypts a file using a caesar cypher with encryption key "offset"
FILE *encrypt(FILE *file, int offset);
// Decrypts a file using a caesar cypher with encryption key "offset"
FILE *decrypt(FILE *file, int offset);

#endif // TEXTANALYSIS_H
