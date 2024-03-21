// Name: Kayla Moorcroft
// Date: 26/01/2023
// File: law-of-sines.c
// Assignment: 2a
// Comments: This program prompts the user for the magnitudes of three angles in degrees (A, B, C), and one side (a) of a triangle, and then uses the supplied values to calculate and display the magnitude of the remaining sides (b and c), using the Law of Sines. The area of the triangle will also be calculated.

#include <stdio.h>
#include <math.h>

#define PI 3.1415926

int main()
{
    // declaring variables
    double A,B,C,a,b,c;
    
    // getting input from the user
    printf("You'll be asked for angles of a triangle (A, B, C) and a corresponding side to angle A (a) \n\n");
    
    printf("Enter the angles of a triangle in degrees, A, B then C: \n");
    scanf("%lf %lf %lf", &A, &B, &C);
    
    printf("\nEnter the side corresponding to Angle A: \n");
    scanf("%lf", &a);
    
    // calculations and output
    b = a*sin(B*PI/180)/sin(A*PI/180);
    c = a*sin(C*PI/180)/sin(A*PI/180);
    
    printf("\nThe side opposite to B has length = %7.3lf \n", b);
    printf("The side opposite to C has length = %7.3lf \n", c);
    printf("The area of the triangle with sides a = %.1lf, b = %.1lf, c = %.1lf is \n\tArea = %.3lf \n\n\n", a,b,c, 0.5*b*c*sin(A*PI/180));
    
    return 0;
}
