#ifndef SCORE_INC_H
#define SCORE_INC_H

#include "variables.h"
#include "bit.h"

enum scoreInc_states {score_WAIT, score_GAME};
int scoreIncTick(int state){
	//------------------------ LOCAL VARIABLES --------------------------
	unsigned char joystickInput = joystick_ADC();
	unsigned char rectangleState = (~PINB >> 1) & 0x07;
	unsigned char button1 = GetBit(~PINC, 0);
	unsigned char button2 = GetBit(~PINC, 1);
	unsigned char button3 = GetBit(~PINC, 2);
	unsigned char button4 = GetBit(~PINC, 3);
	
	//----------------------- STATE TRANSITIONS -------------------------
	switch(state){
		case score_WAIT: // when game starts, start incrementing score
		state = startGame ? score_GAME : score_WAIT;
		break;
		case score_GAME: // when song is over, stop incrementing score
		state = endSong ? score_WAIT : score_GAME;
		break;
		default: state = score_WAIT; break;
	}
	
	//-------------------------- STATE ACTIONS --------------------------
	switch(state){
		case score_WAIT:
		break;
		case score_GAME: // pressing the correct button and strumming during the correct
		// rectangle state increases user's score
		if (rectangleState == 0x01){ // left most rectangle, button1
			if (button1 && (joystickInput == DOWN || joystickInput == UP)){
				scoreOnes++;
			}
		}
		else if (rectangleState == 0x02){ // left middle rectangle, button2
			if (button2 && (joystickInput == DOWN || joystickInput == UP)){
				scoreOnes++;
			}
		}
		else if (rectangleState == 0x03){ // right middle rectangle, button3
			if (button3 && (joystickInput == DOWN || joystickInput == UP)){
				scoreOnes++;
			}
		}
		else if (rectangleState == 0x04){ // right most rectangle, button4
			if (button4 && (joystickInput == DOWN || joystickInput == UP)){
				scoreOnes++;
			}
		}
		if (scoreOnes > 9){ // increments each place value accordingly
			scoreOnes = 0;
			scoreTens++;
			if (scoreTens > 9){
				scoreTens = 0;
				scoreHundreds++;
				if (scoreHundreds > 9){
					scoreHundreds = 0;
					scoreThousands++;
				}
			}
		}
		break;
		default: break;
	}
	return state;
}

#endif