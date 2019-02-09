#ifndef _PWM_TICK_
#define _PWM_TICK_

#include "pwm.h"
#include "variables.h"
enum pwm_states {pwm_INIT, pwm_WAIT, pwm_RUN};
int pwmTick(int state){
	switch(state){
		//-----------------------STATE TRANSITIONS--------------------------
		case pwm_INIT:
		state = pwm_WAIT;
		break;
		case pwm_WAIT: //turn PWM on
		if (startGame == 0x01){
			PWM_on();
			state = pwm_RUN;
		}
		else{
			state = pwm_WAIT;
		}
		break;
		case pwm_RUN:
		state = endSong ? pwm_INIT : pwm_RUN;
		break;
		default:
		state = pwm_INIT;
		break;
	}
	switch(state){
		//-----------------------STATE ACTIONS--------------------------
		case pwm_INIT: // turn PWM off
		PWM_off();
		break;
		case pwm_WAIT:
		break;
		case pwm_RUN:
		set_PWM(noteFrequency); // set song note
		break;
		default:
		break;
	}
	return state;
}

#endif