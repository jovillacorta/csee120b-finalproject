#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "scheduler.h"

//------------------------- SHARED VARIABLES -----------------------------------
#include "variables.h" 
//----------------------- END SHARED VARIABLES ---------------------------------

//--------------------- USER-DEFINED STATE MACHINES ----------------------------
#include "songTick.c"		// iterates through song arrays and sets frequency value
#include "pwmTick.c"		// plays speaker at given frequency
#include "menuTick.c"		// sets menu screen, when select is pressed sets game, score, creds screen
#include "creditsTick.c"	// stays on display credits/score screen until back to menu pressed
#include "LCD_Tick.c"		// sets LCD output
#include "scoreIncTick.c"	// increments score in game mode
#include "scoreDispTick.c"	// writes score to screen, blinks score when game over
//------------------- END USER-DEFINED STATE MACHINES --------------------------

//-------------------------- MAIN SCHEDULER ------------------------------------
int main()
{
	DDRA = 0x00; PORTA = 0xFF; // ADC input for joystick
	DDRB = 0xF1; PORTB = 0x0E; // B3-B1 input; B7-B4, B0 output
	DDRC = 0xC0; PORTC = 0x3F; // LCD control lines 
	DDRD= 0xFF; PORTD = 0x00; // LCD data lines
	
	// Period for the tasks
	unsigned long int songTick_calc = 50;
	unsigned long int pwmTick_calc = 50;
	unsigned long int menuTick_calc = 100;
	unsigned long int LCDTick_calc = 25;
	unsigned long int creditsTick_calc = 50;
	unsigned long int scoreIncTick_calc = 25;
	unsigned long int scoreDispTick_calc = 100;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = 25;

	//Recalculate GCD periods for scheduler
	unsigned long int songTick_period = songTick_calc/GCD;
	unsigned long int pwmTick_period = pwmTick_calc/GCD;
	unsigned long int menuTick_period = menuTick_calc/GCD;
	unsigned long int LCDTick_period = LCDTick_calc/GCD;
	unsigned long int creditsTick_period = creditsTick_calc/GCD;
	unsigned long int scoreIncTick_period = scoreIncTick_calc/GCD;
	unsigned long int scoreDispTick_period = scoreDispTick_calc/GCD;
	
	//Declare an array of tasks
	static task task1, task2, task3, task4, task5, task6, task7;
	task *tasks[] = {&task1, &task2, &task3, &task4, &task5, &task6, &task7};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = songTick_period;//Task Period.
	task1.elapsedTime = songTick_period;//Task current elapsed time.
	task1.TickFct = &songTick;//Function pointer for the tick.

	task2.state = -1;
	task2.period = pwmTick_period;
	task2.elapsedTime = pwmTick_period;
	task2.TickFct = &pwmTick;
	
	task3.state = -1;
	task3.period = menuTick_period;
	task3.elapsedTime = menuTick_period;
	task3.TickFct = &menuTick;
	
	task4.state = -1;
	task4.period = creditsTick_period;
	task4.elapsedTime = creditsTick_period;
	task4.TickFct = &creditsTick;
	
	task5.state = -1;
	task5.period = LCDTick_period;
	task5.elapsedTime = LCDTick_period;
	task5.TickFct = &LCD_Tick;

	task6.state = -1;
	task6.period = scoreIncTick_period;
	task6.elapsedTime = scoreIncTick_period;
	task6.TickFct = &scoreIncTick;
	
	task7.state = -1;
	task7.period = scoreDispTick_period;
	task7.elapsedTime = scoreDispTick_period;
	task7.TickFct = &scoreDispTick;
	
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	ADC_init();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}

