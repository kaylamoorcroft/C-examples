# Text analysis tool in C that performs various operations on a given text file.

- **Word/Character/Punctuation Count:** Print out the number of words, characters, and punctuation in the file. 
- **Substring Search:** Finding and displaying all occurrences of the substring in the text by printing out the whole line from the file but put the substring in double-quotes. 
- **Palindromic Words:** Identify and display all palindromic words in the text. A palindromic word is the same when read backward (e.g., "level" or "radar").
- **Encrypt a File:** Read in a text file and encrypt its content using a Caesar cipher. Creates the encrypted file with a new filename (<originalFilename.caesar>).
- **Decrypt a File:** Read in the encrypted file from the previous step and decrypt the file. The user should supply the decryption offset.

## Using the program

expectedOutput.txt shows the output for each of the 5 functions with sample input.
A sample text file input.txt is provided to demonstrate the functionality of the text analysis tool. 

In the command line, run "make". To start the program, you need to provide the filename as well. 
I.e., to run the program with sample input, run "program "input.txt". 

When the encryption or decryption tool is used, this creates new files for each one. 
To delete all the encryption / decryption files as well as the executable and object files, run "make clean".
