/* 
 * File:	student-list.c 
 * Author:	Kayla Moorcroft 
 * Date:	2024/02/16 - 2024/02/19
 * Version:	1.0 
 * Purpose:	Tool for making list of students that stores the name, ID, GPA
 *		There are functions for:
 * 		- printing a student's details
 * 		- finding the student(s) with the highest GPA
 * 		- sorting the list of students from highest to lowest GPA
 * Notes:	First, you can enter the information to create a group of 5
 *		students. The program performs all the operations mentioned 
 * 		above on this group of students. Then it reads the 
 *		"students.csv" file and makes a list from it. Then performs the
 * 		same operations on these as well.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_LINE_SIZE 100
#define MAX_LINES_IN_FILE 99

// Student struct & pointer to struct data type definition
typedef struct {
    char name[MAX_NAME_LENGTH];
    int id;
    float gpa;
} StudentT, *StudentTP;
// Creates a new StudentTP object (pointer to student struct)
StudentTP constructorStudentTP(const char *name, int id, float gpa) {
    StudentTP this;
    if ((this = malloc(sizeof(StudentT))) == NULL) {
        fprintf(stderr, "Error. Cannot allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(this->name, name);
    // get rid of \n char at end if exist - from fgets that put \n at end
    for (int i = 0; i < MAX_NAME_LENGTH; i++) {
        if (this->name[i] == '\n') {
            this->name[i] = '\0';
            break;
        }
    }
    this->id = id;
    this->gpa = gpa;
    return this;
}
// Prints a single Student's information to stdout when the pointer is passed in
void printStudentTP(StudentTP this) {
    printf("Name: %s, ID: %d, GPA: %.2f\n", this->name, this->id, this->gpa);
}
// just a helper function when reading input to get rid of the '\n' character
void clearLine(void) {
    while(getchar() != '\n')
        ;
}
// finding size of StudentTP array allocated on heap using malloc / calloc
int sizeOfArray(const StudentTP *students) {
    int i;
    for (i = 0; students[i] != NULL; i++) 
        ;
    return i;
}
// prints the student(s) with the highest GPA
// need to pass in StudentTP array pointer allocated on heap
void highestGpa(const StudentTP *students) {
    if (students == NULL) { // empty array
        fprintf(stderr, "Cannot find highest GPA for empty array of students\n");
        exit(EXIT_FAILURE);
    }
    float highest = 0; // keep track of highest gpa
    for (int i = 0; i < sizeOfArray(students); i++) {
        if(students[i]->gpa > highest) { // set new highest gpa
            highest = students[i]->gpa;
        }
    }
    // print out student(s) that have highest gpa
    for (int i = 0; i < sizeOfArray(students); i++) {
        if (students[i]->gpa == highest) {
            printStudentTP(students[i]);
        }
    }
}
// sort students from highest to lowest gpa
// modifies original array
void sortByGpa(StudentTP *students) {
    if (students == NULL) { // empty array
        fprintf(stderr, "Cannot sort empty array of students\n");
        exit(EXIT_FAILURE);
    } // compare each student to rest & then swap if have higher gpa
    for (int i = 0; i < sizeOfArray(students) - 1; i++) {
        for (int j = i + 1; j < sizeOfArray(students); j++) {
            if(students[j]->gpa > students[i]->gpa) { // higher gpa, swap
                StudentTP temp = students[j];
                students[j] = students[i];
                students[i] = temp;
            }
        }
    }
}
// reads in a csv file (<100 lines) and returns a StudentTP array containing the info
// each line needs to be formatted like "firstname lastname,id,gpa" - no spaces after ,
StudentTP *fileToArray(const char *filename) {
    FILE *file; // open file
    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error. Cannot read file %s\n", filename);
    }
    StudentTP *students; // allocate space for array, but not for actual objects yet
    if ((students = malloc(MAX_LINES_IN_FILE * sizeof(StudentTP))) == NULL) {
        fprintf(stderr, "Error. Cannot allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    char *line; // read line from file
    if ((line = malloc(MAX_LINE_SIZE * sizeof(char))) == NULL) {
        fprintf(stderr, "Error. Cannot allocate memory.\n");
        exit(EXIT_FAILURE);
    } // split file with , delimiter 
    for (int i = 0; fgets(line, MAX_LINE_SIZE, file) != NULL; i++) {
        char *name = strtok(line, ",");
        int id = strtof(strtok(NULL, ","), NULL); // don't need end ptr for strtof(), so set null
        float gpa = strtof(strtok(NULL, ","), NULL);
        if ((students[i] = malloc(sizeof(StudentTP))) == NULL) { // allocate space for struct
            fprintf(stderr, "Error. Cannot allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        students[i] = constructorStudentTP(name, id, gpa); // put new student in array
    }
    return students;
}
// Deallocate memory for array: both the array and all the pointers
void freeArray(StudentTP **students) {
    // traverse array and deallocate all StudentTP elements
    int size = sizeOfArray(*students); // because # elements changing, need reference to initial
    for (int i = 0; i < size; i++) {
        free((*students)[i]);
        (*students)[i] = NULL;
    } // free actual array (pointer)
    free(*students);
    *students = NULL;
}
int main(void) {
    int size = 5; // using variable instead of hardcoding, so can change later
    StudentTP *students; 
    // allocating space for array
    if ((students = malloc(size * sizeof(StudentT))) == NULL) {
        fprintf(stderr, "Error. Cannot allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    printf("Let's create a group of 5 students...");
    for (int i = 0; i < size; i++) { // creating array from user input
        char name[MAX_NAME_LENGTH];
        int id;
        float gpa;
        printf("\nPlease enter the following details of the student: \n");
        printf("Name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        printf("ID : ");
        scanf("%d", &id);
        clearLine(); // getting rid of \n char
        printf("GPA: ");
        scanf("%f", &gpa);
        clearLine();
        students[i] = constructorStudentTP((const char*)name, id, gpa);
    } 
    printf("\nHere are all the students: \n"); // printing array
    for (int i = 0; i < size; i++) {
        printStudentTP(students[i]); // function to print 1 studentTP object
    }
    printf("\nStudent(s) with highest GPA: \n");
    highestGpa(students); // print student(s) with highest gpa
    sortByGpa(students); // sort from highest to lowest gpa
    printf("\nHere are the students arranged by GPA: \n");
    for (int i = 0; i < size; i++) { // print out new array
        printStudentTP(students[i]);
    }
    printf("----------------\n\n");
    // reading in file
    StudentTP *studentsFromFile = fileToArray("students.csv");
    printf("Students from file \"students.csv\": \n"); // printing array
    for (int i = 0; i < sizeOfArray(studentsFromFile); i++) {
        printStudentTP(studentsFromFile[i]); // function to print 1 studentTP object
    }
    printf("\nStudent(s) with highest GPA: \n");
    highestGpa(studentsFromFile); // print student(s) with highest gpa
    sortByGpa(studentsFromFile); // sort from highest to lowest gpa
    printf("\nHere are the students arranged by GPA: \n");
    for (int i = 0; i < sizeOfArray(studentsFromFile); i++) { // print out new array
        printStudentTP(studentsFromFile[i]);
    } // free memory that allocated
    freeArray(&students);
    freeArray(&studentsFromFile);
    return EXIT_SUCCESS; // end program
}
