#ifndef SCORE_DISP_H
#define SCORE_DISP_H

#include "variables.h"
#include "io.c"

enum scoreDisp_states {scoreDisp_WAIT, scoreDisp_GAME, scoreDisp_BLINK1, scoreDisp_BLINK2};

unsigned char blinkCount = 5;

int scoreDispTick(int state){
	//------------------------ LOCAL VARIABLES --------------------------
	unsigned char oneSecond = 10;
	unsigned char halfSecond = 5;
	unsigned short HighScore = (1000*highThousands) + (100*highHundreds) + (10*highTens) + (1*highOnes);
	
	//----------------------- STATE TRANSITIONS -------------------------
	switch(state){
		case scoreDisp_WAIT:
		state = (startGame) ? scoreDisp_GAME : scoreDisp_WAIT;
		break;
		case scoreDisp_GAME:
		state = (endSong) ? scoreDisp_BLINK1 :scoreDisp_GAME;
		break;
		case scoreDisp_BLINK1:
		if (i > oneSecond){ // after one second, score blinks blank
			i = 0;
			state = scoreDisp_BLINK2;
			LCD_Cursor(26);
			LCD_WriteData(' ');
			LCD_Cursor(27);
			LCD_WriteData(' ');
			LCD_Cursor(28);
			LCD_WriteData(' ');
			LCD_Cursor(29);
			LCD_WriteData(' ');
		}
		else state = scoreDisp_BLINK1;
		break;
		case scoreDisp_BLINK2:
		if (i > halfSecond){
			i = 0;
			if (blinkCount == 1){ // after done blinking, sets high score if needed,
				// resets score, and goes back to main menu screen
				unsigned char tmpHighScore = (1000*scoreThousands) + (100*scoreHundreds) + (10*scoreTens) + (1*scoreOnes);
				if(tmpHighScore > HighScore){
					highThousands = scoreThousands;
					highHundreds = scoreHundreds;
					highTens = scoreTens;
					highOnes = scoreOnes;
				}
				scoreOnes = scoreTens = scoreHundreds = scoreThousands = 0;
				state = scoreDisp_WAIT;
				goToMenu = 1;
				blinkCount = 5;
			}
			else{ // after half second, score blinks value and blinkCount decreases
				blinkCount--;
				state = scoreDisp_BLINK1;
				LCD_Cursor(26);
				LCD_WriteData('0' + scoreThousands);
				LCD_Cursor(27);
				LCD_WriteData('0' + scoreHundreds);
				LCD_Cursor(28);
				LCD_WriteData('0' + scoreTens);
				LCD_Cursor(29);
				LCD_WriteData('0' + scoreOnes);
			}
		}
		else state = scoreDisp_BLINK2;
		break;
		default: state = scoreDisp_WAIT; break;
	}
	
	//-------------------------- STATE ACTIONS --------------------------
	switch(state){
		case scoreDisp_WAIT:
		break;
		case scoreDisp_GAME: // writes ASCII conversion of each place value onto LCD
		LCD_Cursor(26);
		LCD_WriteData('0' + scoreThousands);
		LCD_Cursor(27);
		LCD_WriteData('0' + scoreHundreds);
		LCD_Cursor(28);
		LCD_WriteData('0' + scoreTens);
		LCD_Cursor(29);
		LCD_WriteData('0' + scoreOnes);
		break;
		case scoreDisp_BLINK1:
		i++;
		break;
		case scoreDisp_BLINK2:
		i++;
		break;
		default: break;
	}
	return state;
}

#endif