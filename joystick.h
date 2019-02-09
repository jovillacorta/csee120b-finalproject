//ADC function for joystick found on: http://maxembedded.com/2011/06/the-adc-of-the-avr/
#include <avr/io.h>

void ADC_init()
{
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned short ADC_read(unsigned char ch)
{
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0x03;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

enum DIRECTIONS {DOWN, UP, LEFT, RIGHT, NONE};

unsigned char joystick_ADC() {
	unsigned short midpoint = 511; // ADC for 10k returns 0-1023
	
	unsigned short x_Axis = ADC_read(0);
	unsigned short y_Axis = ADC_read(1);
	
	if (y_Axis < midpoint - 100) {  // 0-411 returns down
		return UP;
	}
	else if (y_Axis > midpoint + 100){ // 611-1023 returns up
		return DOWN;
	}
	else if (x_Axis < midpoint - 100) { // 0-411 returns RIGHT
		return LEFT;
	}
	else if (x_Axis > midpoint + 100) { // 611-1023 returns LEFT
		return RIGHT;
	}
	else {
		return NONE; //No direction
	}
}