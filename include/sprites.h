#include <Arduino.h>
// #include <LiquidCrystal.h>

//Sprites during the friend screen
byte arm[] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000};

byte foodSpriteArray[] = {
    B00000,
    B01110,
    B11001,
    B10011,
    B10101,
    B01110,
    B00000,
    B00000};

// Left and right side of slime sprite
byte left[] = {
    B00000,
    B00011,
    B00100,
    B01000,
    B01010,
    B01000,
    B10000,
    B11111};

byte right[] = {
    B00000,
    B11000,
    B00100,
    B01010,
    B00010,
    B10001,
    B00001,
    B11111};

// Food Sprites
byte cookieSprite[] = {
    B00000,
    B01110,
    B11001,
    B10011,
    B10101,
    B01110,
    B00000,
    B00000};
byte balloonSprite[] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B01010,
    B00100,
    B00010,
    B00100};

// Minigame Ball Sprites
// used to animate the falling ball
byte currentBall[8];

byte ball1[] = {
    B01110,
    B01110,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};

byte ball2[] = {
    B00000,
    B01110,
    B01110,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000};

byte ball3[] = {
    B00000,
    B00000,
    B01110,
    B01110,
    B01110,
    B00000,
    B00000,
    B00000};

byte ball4[] = {
    B00000,
    B00000,
    B00000,
    B01110,
    B01110,
    B01110,
    B00000,
    B00000};

byte ball5[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B01110,
    B01110,
    B01110,
    B00000};