#ifndef VARIABLES_H
#define VARIABLES_H

unsigned char startGame = 0x00;	//Set by menuTick; Cleared by songTick
//Starts songTick, pwmTick, scoreIncTick/scoreDispTick, and matrixTick

unsigned char endSong = 0; //Set by songTick; Cleared by menuTick
//Stops pwmTick and scoreIncTick; Starts blink in scoreDispTick

unsigned char updateScreen = 0; //Set and Cleared by menuTick
//used by LCD_Tick
char* outputLine1;
char* outputLine2;  //Set by menuTick; Used by LCD_Tick

unsigned char displayCreds = 0x00; //Set and Cleared by menuTick; Used by creditsTick
unsigned char goToMenu = 0;	//Set by creditsTick or scoreDisplayTick; Cleared by menuTick
//Used by menuTick to return to menu after credits/score/gameplay

unsigned char i = 0; //Used for time intervals of oneSecond, halfSecond, etc.

unsigned char scoreOnes = 0;
unsigned char scoreTens = 0;
unsigned char scoreHundreds = 0;   //Set by scoreIncTick; Cleared by scoreDispTick
unsigned char scoreThousands = 0;  //Used by scoreDispTick

unsigned char highOnes = 0;
unsigned char highTens = 0;
unsigned char highHundreds = 0;
unsigned char highThousands = 0;   //Set by scoreDispTick; Used by menuTick
//**NOTE: breaking up score into place values simplifies ascii conversion for LCD screen

#endif