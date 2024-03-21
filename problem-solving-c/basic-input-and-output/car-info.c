// Name: Kayla Moorcroft
// Date: 19/01/2023
// File: car-info.c
// Assignment: 1b
// Comments: This program allows a user to enter the make and model of a vehicle, the year the vehicle was manufactured, and the associated mileage (miles/gallon or MPG). It converts the mileage to litres/100 km, then print out the car’s information

#include <stdio.h>
#include <string.h>

int main()
{
    // declaring variables
    char make[25], model[10];
    int year, mileage;
    
    // getting input from the user
    printf("Enter the make and model of the vehicle: \n");
    scanf("%s %s", make, model);
    
    printf("Enter the year of manufacture: \n");
    scanf("%d", &year);
    
    printf("Enter the fuel mileage (mile/gallon): \n");
    scanf("%d", &mileage);
    
    /*
    CALCULATIONS
    1 gallon = 3.78541 L
    1 mile = 1.60934 km
    miles/gallon * 1.60934/3.78541 = km/L
    1/(km/L) = L/km
    L/km / 100 = L/100km
    Therefore, all in one step:
    1/(miles/gallon * 1.60934/(3.78541*100)) = L/100km
    */
    
    // printing the car's information
    printf("\n\nThe %s %s built in %d uses %.1f L fuel per 100 km\n\n", make, model, year, 1/((float)mileage * 1.60934/(3.78541*100)));
    
    return 0;
}
