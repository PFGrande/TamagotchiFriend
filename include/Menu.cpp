#include "Menu.h"


  Menu::Menu() {
  	
  }
  
  //THE TITLE SCREEN
  void Menu::titleScreen() {
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

  int Menu::returnInput() {
    delay(140);//helps avoid miss-inputs
	int result = 3;//3 means some loops will keep going
    int buttonPress = 0;
    //int ballPhase; for the minigame portion
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
  String Menu::pickName() {
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
  void Menu::drawMainScr() {
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
      Serial.print("button out of bounds");
      break;
    }
    
    
  
  }
  
  //draws the attributes and slime
  void Menu::drawMainUI() {
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
  
  
  void Menu::drawOptions() {
    currentScreen = "options";
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
            	optionsPage = 0;//resets the menu to the top
            	animateFriend();
            	Serial.print("buddy");
            	break;
            case 1:
            optionsPage = 0;
            drawFeed();
            Serial.print("Feed");
            	break;
            case 2: 
            optionsPage = 0;
            minigame();
            Serial.print("game");
            	break;
            case 3: 
            optionsPage = 0;
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
  
  void Menu::animateFriend() {
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
  void Menu::printOptionsMenu(int page) {
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
  void Menu::drawFeed() {
    currentScreen = "feed";
    lcd_1.clear();
  	print_line_to_row("UNFINISHED,", 0, true);
    print_line_to_row("SORRY!", 1, true);
    delay(1000);
  
  
  }
  
  //THIS IS THE MINIGAME
  void Menu::minigame() {
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
  
  void Menu::gameEndScreen() {
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
  
  int Menu::drawBall(int timer, int pos) {//in my test ver. I had it at every 100ms
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
  
  void Menu::copyBall(byte newBall[]) {
    for (int i = 0; i < 8; i++) {
      currentBall[i] = newBall[i];
    }
  }
  
  void Menu::claimPoint() {
    if (ballPositions[ballIndex] == slime.placement || ballPositions[ballIndex] == slime.placement+1) {
      score++;
      print_line_to_row("                ", 0, true);
      ballIndex++;
      Serial.print('\n');      
      Serial.print("currentScore: ");
      Serial.print(score);
      
      
    }
  
  }
  
  void Menu::minigamePrompt() {
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
  
  void Menu::quitTama() {
  	currentScreen = "quit";
    lcd_1.clear();
    print_line_to_row("GREEN - PLAY", 0, true);
    if (returnInput() == 0) {
      lcd_1.clear();
      titleScreen();
    }
    
  
  }
  
  void Menu::gameOverScreen() {
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
  
