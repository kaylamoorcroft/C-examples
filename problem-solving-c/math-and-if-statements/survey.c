// Name: Kayla Moorcroft
// Date: 30/01/2023
// File: survey.c
// Assignment: 2b
// Comments: This program asks a user to respond to 3 questions by ranking level of agreement on a scale of 1 to 5. The survey is set up so that 5 means the user fully supports the statement, down to 1 which represents a user not supporting the statement. The sum of the answers will relate to a message that is displayed on the screen (whether the user supports the project, doesn't support it, or is neutral about it).

/*
 PSEUDOCODE OUTLINE:
 Display the explanation of the survey setup (5 = strongly agree, 1 = strongly disagree)
 Print question 1
 Get user input and store it in q1
 Print question 2
 Get user input and store it in q2
 Print question 3
 Get user input and store it in q3
 Calculate the sum of the user's 3 responses and set sum to this value
 If sum is greater than or equal to 12
    Print that the user is supports the project
 End if
 Else if sum is between 6 and 11 (excluding 6, including 11)
    Print that the user is neutral towards the project
 End else if
 Else
    Print that the user doesn't support the project
 End else
 */

#include <stdio.h>

int main()
{
    // declaring variables
    int q1, q2, q3, sum; // these are the user's responses to each question and the total sum of their responses
    
    // getting input from the user and explaining to them how to answer the questions
    printf("Please answer the following questions on a scale of 1 to 5: \n\t1 = Strongly Disagree, up to 5 = Strongly Agree \n\n");
    
    printf("Question 1: It is important to have a variety of recreational activities available to our residents \n\tAnswer 1-5 > ");
    scanf("%d", &q1);
    
    printf("Question 2: It is important to attract new residents and increase tourism to our community \n\tAnswer 1-5 > ");
    scanf("%d", &q2);
    
    printf("Question 3: I support a potential raise in residential taxes in order to invest in our community \n\tAnswer 1-5 > ");
    scanf("%d", &q3);
    
    // finding the sum of the user's responses and displaying an appropriate output based on the sum
    sum = q1 + q2 + q3;
    
    if (sum >= 12)
        printf("\nYour answers indicate you support this project. \n\n\n");
    else if (sum > 6 && sum <= 11)
        printf("\nYour answers indicate you are neutral about this project. \n\n\n");
    else
        printf("\nYour answers indicate you do not support the project. \n\n\n");
    
    return 0;
}
