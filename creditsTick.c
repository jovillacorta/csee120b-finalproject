#ifndef CREDITS_TICK_H
#define CREDITS_TICK_H

#include "variables.h"
#include "bit.h"

enum credits_States {cred_WAIT, cred_DISPLAY, cred_PRESSMENU};

int creditsTick(int state){
	//------------------------LOCAL VARIABLES --------------------------
	unsigned char selectButton = GetBit(~PINC, 0);
	
	//-----------------------STATE TRANSITIONS--------------------------
	switch(state){
		case cred_WAIT:
		if (displayCreds){
			state = cred_DISPLAY;
		}
		else state = cred_WAIT;
		break;
		case cred_DISPLAY:
		state = selectButton ? cred_PRESSMENU : cred_DISPLAY;
		break;
		case cred_PRESSMENU: // if button is pressed, go back to Menu
		if (selectButton) state = cred_PRESSMENU;
		else{
			goToMenu = 1;
			state = cred_WAIT;
		}
		break;
		default: state = cred_WAIT; break;
	}
	//----------------------- STATE ACTIONS ------------------------------
	// (NONE)
	return state;
}

#endif