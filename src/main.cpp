// C++ code
//
/*
  LiquidCrystal Library - Hello World

   Demonstrates the use of a 16x2 LCD display.
  The LiquidCrystal library works with all LCD
  displays that are compatible with the  Hitachi
  HD44780 driver. There are many of them out
  there, and you  can usually tell them by the
  16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008  by David
  A. Mellis
  library modified 5 Jul 2009  by Limor Fried
  (http://www.ladyada.net)
  example added 9 Jul 2009  by Tom Igoe
  modified 22 Nov 2010  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/
/*I apologize if you can see this code.
* Progress Log:
* Finished title screen.
* Finished name screen
* Finished options menu UI and implementation
* Working on: X = cancelled
*	-pet animatoin and function  <------------ animteArm method!!! (changed animation)
*		-didnt do what I wanted at fiirst but I think its pretty decent
*   -feed and food items X
*	-google dino-like minigame (might not be possible) X
*   -stretch and compression for slime using base, min width, min height
*		-(if I have time I will do this) X
*   -Jump animation might be fun X
*       -for this Ill go from the top center of slime to bottom
*	-I dont want to animate frame-by-frame but I really want to use code to do it
*working on five letter name: tommy? EDDIE!
*	-quit button - done
*	-game over - done
*	-minigame - done
feed game quit
*/

//#include <Arduino.h> moved to the sprites.h file
//#include <LiquidCrystal.h>
//#include "sprites.h"
//#include "DisplayFunctions.h"
//#include "Food.h"
#include "Menu.h"

//int seconds = 0;
//int countRewards = 0;

Menu theScreen;//initializes my scenes





void setup()
{
  Serial.begin(9600);
  pinMode(pinAccept, INPUT);
  pinMode(pinDecline, INPUT);
  pinMode(pinMenu, INPUT);
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD. 
}

void loop()
{
  
  if (namePicked == false) {
  	theScreen.titleScreen();
    lcd_1.clear();
    delay(500);
    lcd_1.print("Hi there " + slime.name + "!");
    delay(500);
    lcd_1.clear();
  }
  delay(1000);

  theScreen.drawMainScr();
  
}
