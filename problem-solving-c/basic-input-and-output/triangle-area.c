// Name: Kayla Moorcroft
// Date: 19/01/2023
// File: triangle-area.c
// Assignment: 1a
// Comments: This program a allows a user to enter the base and height of a triangle and print its area.

#include <stdio.h>

int main()
{
    // declaring variables
    float base, height;
    
    // getting input from the user
    printf("Enter the base measurement of the triangle: \n");
    scanf("%f", &base);
    
    printf("Enter the height measurement of the triangle: \n");
    scanf("%f", &height);
    
    // calculating and displaying the area of the triangle
    printf("\n\nThe area of a triangle with base = %.2f and height = %.2f is %.2f \n\n\n", base, height, 0.5*base*height);
    
    return 0;
}
