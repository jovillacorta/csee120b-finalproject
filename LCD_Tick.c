#ifndef LCD_TICK_H
#define LCD_TICK_H

#include "io.c"

enum LCD_States {LCD_UPDATE};
int LCD_Tick(int state){
	//------------------------ LOCAL VARIABLES --------------------------
	unsigned char line1 = 1;
	unsigned char line2 = 17;
	
	//----------------------- STATE TRANSITIONS -------------------------
	switch (state){
		case LCD_UPDATE: // when updateScreen = 1, display new output on LCD screen
		if (updateScreen != 0){
			LCD_ClearScreen();
			LCD_DisplayString(line1, outputLine1);
			LCD_DisplayString(line2, outputLine2);
		}
		state = LCD_UPDATE;
		break;
		default: state = LCD_UPDATE; break;
	}
	//-------------------------- STATE ACTIONS --------------------------
	//(NONE)
	return state;
}

#endif
