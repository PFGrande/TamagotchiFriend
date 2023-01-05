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

#include <Arduino.h>
#include <LiquidCrystal.h>



int seconds = 0;

int pinAccept = 8;
int pinDecline = 9;
int pinMenu = 10;
int countRewards = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

bool namePicked = false;

char characters[5] = {48, 48, 48, 48, 48}; //columns for name

byte arm[] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

byte foodSpriteArray[] = {
  B00000,
  B01110,
  B11001,
  B10011,
  B10101,
  B01110,
  B00000,
  B00000
};

byte left[] = {
  B00000,
  B00011,
  B00100,
  B01000,
  B01010,
  B01000,
  B10000,
  B11111
};

byte right[] = {
  B00000,
  B11000,
  B00100,
  B01010,
  B00010,
  B10001,
  B00001,
  B11111
};

//Types of food sprites:
byte cookieSprite[] = {
      	B00000,
        B01110,
        B11001,
        B10011,
        B10101,
        B01110,
        B00000,
        B00000
      };
byte balloonSprite[] = {
        B01110,
        B10001,
        B10001,
        B10001,
        B01010,
        B00100,
        B00010,
        B00100
      }; 

//THE FOLLOWING ARE BALL SPRITES
byte currentBall[8];

byte ball1[] = {
  B01110,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte ball2[] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};

byte ball3[] = {
  B00000,
  B00000,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000
};
byte ball4[] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000
};
byte ball5[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B01110,
  B00000
};

class Food {
  public:
  String type;
  int nutrition;
  
  
  Food(String foodGained, int nutritionGained){
  	type = foodGained;
    nutrition = nutritionGained;
    countRewards++;
  
  }
  
  
  void setFoodSprite() {
    if (type == "cookie") {
      copyArray(cookieSprite);
    } else if (type == "balloon") {
      copyArray(balloonSprite);
    }  
  }
  
  void copyArray(byte copyFrom[]){
    for (int i = 0; i < 8; i++) {
      foodSpriteArray[i] = copyFrom[i];
    
    }
    lcd_1.createChar(4, foodSpriteArray);
  }
  
  void printFood() {
  	lcd_1.setCursor(0,2);
    lcd_1.write(4);
    
  
  
  }
  



};

class Pet {
  
  public:
  String name;
  int hunger = 5;
  int joy = 5;
  int sad = 0;
  int counter = 0;
  int placement = 0;
  //Food foodInventory[5];
  
  Pet(String enteredName) {
  	name = enteredName;
  
  }
  
  //draw slime - 1bottL 2bottR 3center
  void drawSlime (int location) {
    switch(location) {
      case 1:
        lcd_1.setCursor(0,1);
    	lcd_1.write(1);
    	lcd_1.setCursor(1,1);
  		lcd_1.write(2);
      	break;      
      
      case 2:
        lcd_1.setCursor(14,1);
    	lcd_1.write(1);
    	lcd_1.setCursor(15,1);
  		lcd_1.write(2);
      	break;
      case 3:
      	lcd_1.setCursor(7,1);
    	lcd_1.write(1);
    	lcd_1.setCursor(8,1);
  		lcd_1.write(2);
    	break;
    
    
    }
  	
  }
  //HOW MOVED IN MINIGAME
  void moveSlime(int moved) {
    
    //relative to left side position should not go over or under these
    if (placement == 0) {
      moved = 0;
    } else if(placement == 15) {
      moved = 15;
    }
  	lcd_1.setCursor(moved, 1);
    lcd_1.write(1);
    lcd_1.setCursor(moved+1, 1);
    lcd_1.write(2);
    
  }
  //Following methods will occur in certain time intervals.
  //Joy will deplete for as long as no activities are done
  void depleteStats() {
    counter++;
    //Serial.print(counter);
    //Serial.print(" ");
    if (counter > 100 && joy > 0 && counter < 102) {
    	joy = joy - 1;
      	lcd_1.clear();//clears to hunger and joy maxs dont overlap
    }
    if (counter > 200 && hunger > 0 && counter < 202) {
      hunger = hunger - 1;
      counter = 0;
      lcd_1.clear();//clears to hunger and joy maxs dont overlap
    }
    /*for (int i = 0; i < 15 - joy) {
    	
    
    }*/
  }
  
  /*void increaseSad() {
    if(hunger < 10) {
    	
    
    }
  }*/
  
  void incrementStats(int addJoy, int addHunger) {
  	joy = joy + addJoy;
  	hunger = hunger + addHunger;
    if (joy > 15) {
      joy = 15;
    }
  
    if (hunger > 15) {
      hunger = 15;
    
    
    }
  }
  

};

Pet slime("default");

class Menu {

  public:
  String name;
  //int counter = 0;
  String currentScreen;
  int ballPhase = 0;
  int ballPos;
  int ballPositions[14] = {5, 7, 4, 5, 6, 9, 13, 11, 8, 5, 7, 4, 2, 0};//pos on x axis
  int ballIndex; 
  int score = 0;
    
  Menu() {
  	
  }
  
  //THE TITLE SCREEN
  void titleScreen() {
    currentScreen = "title";
  	lcd_1.print("Welcome!");
  	delay(500);
  	lcd_1.clear();
  	
    if (namePicked == false) {
      //naming part
      lcd_1.print("name it:");

      //draws slime guy/bob 
      lcd_1.createChar(1, left);
      lcd_1.createChar(2, right);
      lcd_1.setCursor(14,1);
      lcd_1.write(1);
      lcd_1.setCursor(15,1);
      lcd_1.write(2);
      

      //triggers name ui
      //Serial.print("name time");
      name = pickName();
      slime.name = name;
      Serial.print(slime.name);
      namePicked = true;
     
    }
    

  }
  
  
  int returnInput() {
    delay(140);//helps avoid miss-inputs
	int result = 3;//3 means some loops will keep going
    int buttonPress = 0;
    //int ballPhase;//for the minigame portion
    
    /*I could probably just check if the result is equal to 3
    but ill just play it safe because i dont want to mess up
    
    */
    
    do {
      if (currentScreen == "main") {
      	slime.depleteStats();
        drawMainUI();
        if (slime.hunger == 0 && slime.joy == 0) {
          gameOverScreen();	
        
        }
      
      } 
     if(digitalRead(pinAccept) == HIGH) {
         //lcd_1.print("ok");
         result = 0;
         buttonPress++;
         //return 0;
     } else if(digitalRead(pinDecline) == HIGH){
         //lcd_1.print("NOOOOOOOO");
         result = 1;
         buttonPress++;
         //return 1;
     } else if(digitalRead(pinMenu) == HIGH) {
         //lcd_1.print("menu");
         buttonPress++;
         result = 2;
         //return 2;	
     } 
      
      
       if (currentScreen == "minigame") {
      	//ball method goes here.
         delay(200);
         if (ballIndex > 14) {
         	ballIndex = 0;
         
         }
         //ballIndex++;
          ballPhase++;
          claimPoint();//by connecting it to movement/inputs i know where player is 100% of the time
         
         drawBall(ballPhase, ballPositions[ballIndex]);
      	 //claimPoint();
         //ballIndex++;
      }
      
    } while (result == 3);
   
    delay(100);//delays result to elimnate any holding
    
    return result;
    
    
  }
  //PICK NAME SCREEN
  String pickName() {
    currentScreen = "name";
  	String enteredName = "BOB";
    int currentIndex = 0;//index of the lcd 0-4
    printArray(characters, 0, 1, 5);
    delay(100);
    
    int userInput;
    char onChar;//Current char user is on in column
    //Allows the user to enter chars for name
    do {
      onChar = 65;
      
      //I think I must reset user input after this!!! or else itll stay at 2
      //I was right B)
      while (userInput != 2) {
        //name bug has been squashed (the one where first char was displayed as A
        lcd_1.setCursor(currentIndex, 1);//new
        lcd_1.print(onChar);//new
        userInput = returnInput();
        //delay(150);//delays to prevent multiple clicks on home button
        //lcd_1.setCursor(currentIndex, 1);//moves cursor to where we are
        if (onChar > 90) {//checks if user is going out of A-Z
        	onChar = 65;
        } else if (onChar < 65) {
        	onChar = 90;
        //switched because it was unintuative
        } else if (userInput == 1){//this was once 0
        	onChar++;        
        } else if (userInput == 0) {//this was once 1
        	onChar--;
        }
      }
      userInput = 3;//resets so loop above works
      //Serial.println(currentIndex + " current i");
      characters[currentIndex] = onChar;//sends the picked char to array
      currentIndex++;//increments index
      //lcd_1.setCursor(currentIndex, 1);
      printArray(characters, 0, 1, 5);//0 used to be currentIndex for some reason
      //Serial.print(characters);
      //Serial.print("  ");
      

          
    } while(characters[4] == 48);//not sure what to put here yet
    printName(characters);
    Serial.print("IDID IT");
    enteredName = characters;

  	return enteredName;
  }
  
  //Main screen will run until the user chooses to to draw options and quit
  void drawMainScr() {
    currentScreen = "main";
    int userInput;
    
    drawMainUI();
    userInput = returnInput();
    Serial.print(userInput);
  	
    switch (userInput) {
      case 0:
      Serial.print("button1");
      break;
      case 1: 
      Serial.print("button2");
      break;
      case 2: 
      drawOptions();
      break;
      default:
      Serial.print("my code sucks lol");
      break;
    }
    
    
  
  }
  
  //draws the attributes and slime
  void drawMainUI() {
    //returns error if i try mixing ints and chars/strings in .print
    lcd_1.setCursor(0,0);
    lcd_1.print("H:");
    lcd_1.print(slime.hunger);
    lcd_1.print("/15");
    lcd_1.setCursor(0,1);
    lcd_1.print("J:");
    lcd_1.print(slime.joy);
    lcd_1.print("/15");
    slime.drawSlime(2);
    
  }
  
  
  void drawOptions() {
    currentScreen = "options";
  	//Serial.print("these are the options"); works
    lcd_1.clear();
    int userInput;
    int optionsPage = 0;
    do {
      if (optionsPage >= 4) {
      	optionsPage = 0;
      
      }
      printOptionsMenu(optionsPage);
      userInput = returnInput();
      
      
      switch(userInput) {
        case 0:
          //enters option chosen by user
        lcd_1.clear();
          switch(optionsPage) {
          	case 0: 
            	optionsPage = 0;//new, resets the menu to the top
            	animateFriend();
            	Serial.print("buddy");
            	break;
            case 1:
            optionsPage = 0;//new, resets the menu to the top
            drawFeed();
            Serial.print("Feed");
            	break;
            case 2: 
            optionsPage = 0;//new, resets the menu to the top
            minigame();
            Serial.print("game");
            	break;
            case 3: 
            optionsPage = 0;//new, resets the menu to the top
            quitTama();
            Serial.print("jump");
            	break;
          }
        
          break;
        case 2:
          //printOptionsMenu(optionsPage % 2);
          optionsPage++;
          printOptionsMenu(optionsPage);
          break;
        default:
          Serial.print("my code is bad haha");
          break;
      }

    
    } while (userInput != 1);//stops when button 2/B/red button is pressed
    //goes back to main menu after b button
    lcd_1.clear();//smoother transition
    drawMainUI();
  }
  
  void animateFriend() {
    currentScreen = "friend";
    int armBottom = 5;//bottom of arm sprite
    byte temp;
    
    for(int i = 0; i < 4; i++) {
      slime.drawSlime(3);
      
      print_line_to_row(" A   A Hi there!", 0, true);
      delay(200);
      for (int i = 0; i < 7; i++) {
        
        lcd_1.setCursor(i,1);
        lcd_1.write(3);
        delay(200);
        arm[6-i] = B11111;
        arm[i] = B00000;
        lcd_1.createChar(3, arm);
        print_line_to_row(" A   A Hi " + slime.name + "!", 0, true);
        //delay(200);


    	}
    
    }
    
    slime.incrementStats(1, 0);
  	delay(1000);
  }
  
  //returns the option selected by the user; (was not necessary lol)
  //Why did I put a semicolon there?
  
  //will be navigated with home button/C, exited with red button/B
  void printOptionsMenu(int page) {
    String optionsTxt[4] = {
    	"1.Buddy",
      	"2.Feed",
      	"3.Game",
      	"4.Quit"
    };
    
    lcd_1.clear();//fixes growing arrow bug
    //bug originated from the area the arrow was in not being cleared haha
    print_line_to_row(optionsTxt[page], 0, false);
   	//lcd_1.setCursor((optionsTxt[page].length())+2, 0);
    //lcd_1.print("<-");
    print_line_to_row(optionsTxt[page+1], 1, false);
  }
  
  //THIS IS WHERE SLIME IS FED
  void drawFeed() {
    currentScreen = "feed";
    lcd_1.clear();
  	print_line_to_row("UNFINISHED,", 0, true);
    print_line_to_row("SORRY!", 1, true);
    delay(1000);
  
  
  }
  
  //THIS IS THE GOOGLE DINASOUR CLONE
  void minigame() {
    minigamePrompt();
    currentScreen = "minigame";//moved down so ball dont instantly spawn

    int score;
    int userInput;
    int slimePos = 7;

    do {
      lcd_1.setCursor(0,1);
      lcd_1.print("                ");
      slime.placement = slimePos;
      //claimPoint();//checks before user inputs anything
      slime.moveSlime(slimePos);
      userInput = returnInput();
      //old slime.placement = slimePos;
      
      switch(userInput) {
      	case 0:
        if (slimePos != 0) {
          slimePos--;
        }
        //oldslimePos--;
        break;
        case 1:
        if (slimePos != 14) {
          slimePos++;
        
        }
        //oldslimePos++;
        break;
      	default:
        slime.moveSlime(slimePos);
        break;
      
      }  
      //I have to draw slime on specific coords
      //I can do if they are on the same x axis then they can
      //get a point Ill save the score for the end of the game
    
    }while(userInput != 2);
    
    gameEndScreen();
  
  
  }
  
  void gameEndScreen() {
    currentScreen = "minigameEnd";
    lcd_1.clear();
    print_line_to_row("Score: ", 0, true);
    lcd_1.setCursor(0,1);
    lcd_1.print(score);
    slime.drawSlime(3);
    // -- cleans up values for game --
    delay(2000);
    score = 0;
    ballIndex = 0;
    ballPhase = 0;
    slime.incrementStats(3, 0);
    
  
  }
  
  int drawBall(int timer, int pos) {//in my test ver. I had it at every 100ms
    int animationStage;
    animationStage = timer%10;//was mod 5 but it was too fast 
    switch(animationStage) {
      case 0:
      case 1:
          copyBall(ball1);
      break;
      case 2:
      case 3:
          copyBall(ball2);
      break;
      case 4:
      case 5:
          copyBall(ball3);
      break;
      case 6:
      case 7:
          copyBall(ball4);
      break;
      case 8:
      case 9:
          copyBall(ball5);
      break;
      default:
      lcd_1.print("failure");
      break;

    }
    
    lcd_1.createChar(5, currentBall);
  	lcd_1.setCursor(pos, 0);//PLACE POS VAL HERE
  	lcd_1.write(5);
    if(animationStage == 9) {
      print_line_to_row("                ", 0, true);
      ballIndex++; //old
      //print_line_to_row("                ", 0, true);
    
    }
    return animationStage;
  }
  
  void copyBall(byte newBall[]) {
    for (int i = 0; i < 8; i++) {
      currentBall[i] = newBall[i];
    }
  }
  
  void claimPoint() {
    if (ballPositions[ballIndex] == slime.placement || ballPositions[ballIndex] == slime.placement+1) {
      score++;
      print_line_to_row("                ", 0, true);
      ballIndex++;
      Serial.print('\n');      
      Serial.print("currentScore: ");
      Serial.print(score);
      
      
    }
  
  }
  
  void minigamePrompt() {
    currentScreen = "gameintro";
  	int userInput;

    do {
      print_line_to_row("CONTROLS:", 0, true); 
      print_line_to_row("GREEN - JUMP", 1, true); 
      delay(1500);
      lcd_1.clear();
      
      print_line_to_row("BLUE - EXIT", 0, true);
      delay(1500);
      print_line_to_row("CONT PRESS GREEN", 1, true); 
      userInput = returnInput();
      
    
    } while(userInput != 0);
    lcd_1.clear();
    lcd_1.setCursor(5,0);
    lcd_1.print("START!");
    delay(700);
    lcd_1.clear();
  
  
  
  }
  
  void quitTama() {
  	currentScreen = "quit";
    lcd_1.clear();
    print_line_to_row("GREEN - PLAY", 0, true);
    if (returnInput() == 0) {
      lcd_1.clear();
      titleScreen();
    }
    
  
  }
  
  void gameOverScreen() {
  	currentScreen = "gameover";
    String sadMessage = slime.name + " has left.";
    lcd_1.clear();
    print_line_to_row(sadMessage, 0, true);
    namePicked = false;
    slime.hunger = 15;
    slime.joy = 15;
    slime.name = "default";
    for (int i = 0; i < 5; i++) {
      characters[i] = 48;
    
    }
    
    delay(1000);
    lcd_1.clear();
    lcd_1.setCursor(0,0);
    titleScreen();
  
  
  }

Menu theScreen;//initializes my scenes
//Pet slime("default");




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
  //slime.counter++;
  theScreen.drawMainScr();
  
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  //lcd_1.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd_1.print(seconds);
  //delay(1000); // Wait for 1000 millisecond(s)
  //seconds += 1;
}

void printArray(char array[], int startingX, int startingY, int size) {
  int temp1 = startingX;//Y doesnt change so does not have to be saved
  //5 is had coded because for some reason the size of method is not working for me
  for (int i = 0; i < size; i++){
    lcd_1.setCursor(startingX, startingY);
  	lcd_1.print(array[i]);
    startingX++;
    
  }
  lcd_1.setCursor(temp1, startingY);//resets the cursor

}

void printName (char array[]) {
  for (int i = 0; i < 5; i++) {
  	Serial.print(array[i]);
  
  }

}

void print_line_to_row (String line, int row, bool removeArrow) {
	lcd_1.setCursor(0, row);
	lcd_1.print(line);
  if (row == 0 && removeArrow == false) {
    
   	lcd_1.setCursor((line.length())+2, 0);
    lcd_1.print("<-");  
  
  }
}