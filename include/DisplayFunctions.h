#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2); // Pins used by LCD

// Prints the character's name on LCD screen
void printArray(char array[], int startingX, int startingY, int size); 

//void printName (char array[]);

//Prints to a row, starting at the start of the defined row 
void print_line_to_row (String line, int row, bool removeArrow);

#endif //PRINT_FUNCTION_H