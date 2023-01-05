#include "sprites.h"
#include "DisplayFunctions.h"
#include "Pet.h"

#ifndef MENU_H
#define MENU_H

int pinAccept = 8;
int pinDecline = 9;
int pinMenu = 10;
bool namePicked = false;
char characters[5] = {48, 48, 48, 48, 48}; //columns for name
Pet slime("default");

class Menu {

public:
    String name;
    // int counter = 0;
    String currentScreen;
    int ballPhase = 0;
    int ballPos;
    int ballPositions[14] = {5, 7, 4, 5, 6, 9, 13, 11, 8, 5, 7, 4, 2, 0}; // pos on x axis
    int ballIndex;
    int score = 0;

    Menu();

    // TITLE SCREEN
    void titleScreen();

    // Takes user input
    int returnInput();

    // PICK NAME SCREEN
    String pickName();

    // Main screen will run until the user chooses to to draw options and quit
    void drawMainScr();

    // draws the attributes and slime
    void drawMainUI();

    void drawOptions();

    void animateFriend();

    // returns the option selected by the user; (was not necessary lol)
    // Why did I put a semicolon there?

    // will be navigated with home button/C, exited with red button/B
    void printOptionsMenu(int page);

    // THIS IS WHERE SLIME IS FED
    void drawFeed();

    // Minigame plays
    void minigame();

    // Minigame end screen
    void gameEndScreen();

    // Places ball
    int drawBall(int timer, int pos);

    // currentBall array is reset with the original values of balls
    void copyBall(byte newBall[]);

    // Point granted when user collides with ball
    void claimPoint();

    // game instructions
    void minigamePrompt();

    // Pause menu?
    void quitTama();

    // game over when tamagotchi is not fed or played with
    void gameOverScreen();
};

#endif //MENU_H