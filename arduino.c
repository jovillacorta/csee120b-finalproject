//sources:
//LED CONTROL LIBRARY FOUND AT: https://github.com/wayoda/LedControl
#include <LedControl.h>
#include <Arduino.h>

LedControl lc=LedControl(12,11,10,1);
int startGame = A3;
int state0 = A0;
int state1 = A1;
int state2 = A2;

byte currentScreen[8];
byte one = B11000000; //left most two bits
byte two = B00110000; //middle-left two bits
byte three = B00001100; //middle-right two bits
byte four = B00000011; //right most two bits
byte rest = B00000000; //no bits
int countShifts = 0;

byte threeScreen[8] = {B01111100,
	B01111110,
	B00000110,
	B00111100,
	B00111110,
	B00000110,
	B01111100,
B01111100};
byte twoScreen[8] = {B01111100,
	B01111110,
	B00000110,
	B00011100,
	B00111000,
	B01100000,
	B01111110,
B01111110};
byte oneScreen[8] = {B00011000,
	B00111000,
	B00011000,
	B00011000,
	B00011000,
	B00011000,
	B00011000,
B00111100};

byte rectangleArray[75] = {one, rest, four, three, two, rest,
	one, rest, four, three, two, rest,
	two, one, rest, one, rest, four, three, two, three, rest,
	one, two, three, rest, one, two, three, rest,
	one, two, three, rest, one, two, three, one, rest,
	four, three, two, rest, one, rest, four, three, two, rest,
	three, four, rest,
	four, rest, one, three, two, one, rest,
	one, three, two, rest, one, three, two, rest,
one, three, two, rest, one, three, two, three};
int rectangleLength[75] = {8, 1, 2, 4, 18, 1,
	8, 1, 2, 4, 8, 1,
	4, 4, 1, 8, 1, 2, 4, 14, 4, 1,
	2, 2, 2, 1, 2, 2, 2, 1,
	2, 2, 2, 1, 2, 2, 2, 8, 1,
	2, 4, 18, 1, 8, 1, 2, 4, 8, 1,
	4, 4, 1,
	8, 1, 2, 4, 14, 4, 1,
	2, 2, 2, 1, 2, 2, 2, 1,
	2, 2, 2, 1, 2, 2, 4, 16
};
const long tempo = 50;
//long unsigned int lastUpdateTime = 0;

void shiftDownOne(byte newRow){
	for (int i = 7; i >= 1; i--){
		currentScreen[i] = currentScreen[i-1];
	}
	currentScreen[0] = newRow;
}

void checkState(){
	if (currentScreen[7] == rest){
		digitalWrite(state2, HIGH);
		digitalWrite(state1, HIGH);
		digitalWrite(state0, HIGH);
	}
	else if (currentScreen[7] == one){
		digitalWrite(state2, HIGH);
		digitalWrite(state1, HIGH);
		digitalWrite(state0, LOW);
	}
	else if (currentScreen[7] == two){
		digitalWrite(state2, HIGH);
		digitalWrite(state1, LOW);
		digitalWrite(state0, HIGH);
	}
	else if (currentScreen[7] == three){
		digitalWrite(state2, HIGH);
		digitalWrite(state1, LOW);
		digitalWrite(state0, LOW);
	}
	else if (currentScreen[7] == four){
		digitalWrite(state2, LOW);
		digitalWrite(state1, HIGH);
		digitalWrite(state0, HIGH);
	}
}

void emptyScreen() {
	for (int row = 0; row<8; row++){
		currentScreen[row] = B00000000;
	}
	displayScreen();
}

void fullScreen(){
	for (int row = 0; row<8; row++){
		currentScreen[row] = B11111111;
	}
	displayScreen();
}

void displayScreen(){
	for (int row = 0; row < 8; row++){
		lc.setRow(0, row, currentScreen[row]);
	}
}

void countDown(){
	for (int i = 0; i < 8; ++i){
		currentScreen[i] = threeScreen[i];
	}
	displayScreen();
	delay(1000);
	for (int i = 0; i < 8; ++i){
		currentScreen[i] = twoScreen[i];
	}
	displayScreen();
	delay(1000);
	for (int i = 0; i < 8; ++i){
		currentScreen[i] = oneScreen[i];
	}
	displayScreen();
	delay(1000);
	emptyScreen();
}

void drawRectangles(byte noteArray[], int noteDurations[]){
	for (int i = 0; i < 75; i++){
		for (int j = 0; j < noteDurations[i]; ++j){
			shiftDownOne(noteArray[i]);
			displayScreen();
			checkState();
			countShifts++;
			if (currentScreen[7] == rest) delay(tempo);
			else delay(tempo*2);

		}
	}
	for (int i = 0; i < 8; i++) {
		shiftDownOne(rest);
		delay(tempo*2);
		displayScreen();
	}
	countShifts = 0;
}

void setup() {
	lc.shutdown(0,false);
	// Set brightness to a medium value
	lc.setIntensity(0,4);
	// Clear the display
	lc.clearDisplay(0);
	
	pinMode(startGame, INPUT);
	pinMode(state0, OUTPUT);
	pinMode(state1, OUTPUT);
	pinMode(state2, OUTPUT);
	// put your setup code here, to run once:

}

void loop() {
	emptyScreen();
	
	if (digitalRead(startGame)){
		countDown();
		drawRectangles(rectangleArray, rectangleLength);
		delay(500);
		for(int i = 0; i <3; ++i){
			emptyScreen();
			delay(500);
			fullScreen();
			delay(500);
		}
	}
}
// put your main code here, to run repeatedly:

