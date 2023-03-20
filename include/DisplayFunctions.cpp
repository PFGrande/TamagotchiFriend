#include "DisplayFunctions.h"

// Prints the character's name on LCD screen
void printArray(char array[], int startingX, int startingY, int size) {
  int temp1 = startingX; //Y doesnt change so does not have to be saved
  //5 is had coded because for some reason the sizeOf() is not working for me
  for (int i = 0; i < size; i++){
    lcd_1.setCursor(startingX, startingY);
  	lcd_1.print(array[i]);
    startingX++;
    
  }
  lcd_1.setCursor(temp1, startingY);//resets the cursor

}

//Prints the character's name in the console
// void printName (char array[]) {
//   for (int i = 0; i < 5; i++) {
//   	Serial.print(array[i]);
  
//   }

// }

//Prints to a row, starting at the start of the defined row 
void print_line_to_row (String line, int row, bool removeArrow) {
	lcd_1.setCursor(0, row);
	lcd_1.print(line);
  if (row == 0 && removeArrow == false) {
    
   	lcd_1.setCursor((line.length())+2, 0);
    lcd_1.print("<-");  
  
  }
}