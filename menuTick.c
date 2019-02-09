#ifndef MENU_TICK_H
#define MENU_TICK_H

#include "joystick.h"
#include "bit.h"
#include "variables.h"
#include "io.h"

enum menu_States {menu_INIT, menu_WELCOME, menu_MAIN, menu_DOWN, menu_UP,
menu_SELECTPRESS, menu_SELECTRELEASE};

const unsigned char menuSize = 3;
char *welcomeLine1 = "   Welcome to   ";
char *welcomeLine2 = "Guitar Hero Game";
char *menuTitle = "***MAIN MENU*** ";
char *menuSubtitle[] = {"  Play Game", "  High Score", "  Credits"};
unsigned char userChoice = 0;

int menuTick(int state){
	//------------------------ LOCAL VARIABLES --------------------------
	unsigned char oneSecond = 10;
	unsigned char joystickInput = joystick_ADC();
	unsigned char selectButton = GetBit(~PINC, 0);
	unsigned char startButton = GetBit(~PINC, 3);
	//PORTB = PORTB & 0xFE; //Clear bit0
	//PORTB = PORTB | startGame; //Set bit 0 to startGame

	//----------------------- STATE ACTIONS ------------------------------
	switch(state){
		case menu_INIT:
		userChoice = 0;
		outputLine1 = welcomeLine1;
		outputLine2 = welcomeLine2;
		updateScreen = 1;
		break;
		case menu_WELCOME:
		updateScreen = 0;
		break;
		case menu_MAIN:
		updateScreen = 0;
		break;
		case menu_DOWN:
		i++;
		updateScreen = 0;
		break;
		case menu_UP:
		i++;
		updateScreen = 0;
		break;
		case menu_SELECTPRESS:
		break;
		case menu_SELECTRELEASE:
		updateScreen = 0;
		break;
	}
	
	//----------------------- STATE TRANSITIONS -------------------------
	switch(state){
		case menu_INIT:
		state = menu_WELCOME;
		break;
		case menu_WELCOME: //welcome screen, press start to get to main menu
		if (startButton){
			state = menu_MAIN;
			outputLine1 = menuTitle;
			outputLine2 = menuSubtitle[0];
			updateScreen = 1;
		}
		else state = menu_WELCOME;
		break;
		case menu_MAIN: // main menu selection screen; sets LCD to menu options
		if ((joystickInput == DOWN) && (selectButton==0)){
			state = menu_DOWN;
			if (userChoice < (menuSize -1)){
				userChoice++;
			}
			else {
				userChoice = menuSize - 1;
			}
			outputLine2 = menuSubtitle[userChoice];
			updateScreen = 1;
		}
		else if ((joystickInput == UP) && (selectButton==0)){
			state = menu_UP;
			if (userChoice > 0){
				userChoice--;
			}
			else{
				userChoice = 0;
			}
			outputLine2 = menuSubtitle[userChoice];
			updateScreen = 1;
		}
		else if (selectButton){
			state = menu_SELECTPRESS;
		}
		else state = menu_MAIN;
		break;
		case menu_DOWN: // when joystick is held, scroll down at a rate of once per second
		if (joystickInput == DOWN && i < oneSecond){
			state = menu_DOWN;
		}
		else {
			state = menu_MAIN;
			i = 0;
		}
		break;
		case menu_UP: // when joystick is held, scroll up at a rate of once per second
		if (joystickInput == UP && i < oneSecond){
			state = menu_UP;
		}
		else {
			state = menu_MAIN;
			i = 0;
		}
		break;
		case menu_SELECTPRESS:	// if select is held, do nothing
		// if select is released, set lcd screen based on userChoice
		if (selectButton) state = menu_SELECTPRESS;
		else {
			if (userChoice == 0){
				outputLine1 = "GAME IN PROGRESS";
				outputLine2 = "  Score:";
				updateScreen = 1;					//display game play
				startGame = 0x01;					//game play begin
				endSong = 0x00;					//song begin
			}
			else if (userChoice == 1){
				displayCreds = 0x01;
				outputLine1 = "***HIGH SCORE***";
				outputLine2 = "";
				updateScreen = 1;					//display score
			}
			else if (userChoice == 2){
				displayCreds = 0x01;
				outputLine1 = "****CREDITS**** ";
				outputLine2 = "By J. Villacorta";
				updateScreen = 1;					//display credits
			}
			state = menu_SELECTRELEASE;
		}
		break;
		case menu_SELECTRELEASE:	// when select is released, set LCD screen accordingly and
		// wait for goToMenu to be set
		if (userChoice == 1){			//writes score only if High Score screen on
			LCD_Cursor(23);
			LCD_WriteData('0' + highThousands);
			LCD_Cursor(24);
			LCD_WriteData('0' + highHundreds);
			LCD_Cursor(25);
			LCD_WriteData('0' + highTens);
			LCD_Cursor(26);
			LCD_WriteData('0' + highOnes);
		}
		if (goToMenu) {		  //if goToMenu is set, return to menu where user left off
			outputLine1 = menuTitle;
			outputLine2 = menuSubtitle[userChoice];
			updateScreen = 1;
			goToMenu = 0;
			displayCreds = 0;
			state = menu_MAIN;
		}
		else state = menu_SELECTRELEASE;
		break;
		default: state = menu_INIT; break;
	}
	return state;
}
#endif