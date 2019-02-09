# Summary:
Guitar Hero is a series of music-rhythm games in which players press buttons with one hand and “strum” a separate button in the other. This is all done to the beat of music, mimicking an electric or bass guitar. Notes of a song’s melody or base are represented by colored circles/bars that scroll down the screen. Players match these notes accordingly, by pressing or holding down the corresponding buttons for as long as a note is played. 

My project is a simplified version of the game. The game communicates with the user through an LCD screen display. Basic push buttons are used for the guitar fret buttons and a joystick for the strumming function. When the game begins, a piezo buzzer plays the music and an 8x8 LED Matrix mimics the classic falling notes of the original game. Similar to the actual Guitar Hero games, the game requires skill in rhythm and beats, as players are scored based on their accuracy in pressing the right buttons at the right time. 
# User Guide:
The game first takes the player to a Welcome Screen. Pressing the _start_ button will bring the player to the Main Menu screen. 

The menu has three options: *Play Game*, *High Score*, and *Credits*: 

- *Play Game* will take user to Game Mode. The game screen will count down from three, then the game will begin. The player’s objective is to press the corresponding button when a musical note hits the bottom of the screen. The player must also “strum” when a note reaches the bottom by moving the joystick up or down (either is accepted) and holding it for the duration of the note. In order for a note to count for scoring, both the button press and strum must be detected. The players score will increase based on their accuracy in hitting these notes. When the game is over, the score will blink four times before returning to the main menu.
- *High Score* will display the user’s high score. Pressing the _select_ button again will take the user back to the Main Menu screen. If during Game Mode the user achieves a score higher than the current high score, high score is updated accordingly.
- *Credits* will display the name of the game creator. Pressing the select button again will take the user back to the Main Menu screen.

# Technologies and Components:
- AVR Studio 7
- ATMega1284p microcontroller
- Arduino IDE
- Arduino Uno R3 microcontroller
- 8x8 LED Matrix with MAX7219 driver
- Piezo Buzzer
- Buttons
- Joystick
- LCD Screen

# Links:
- Microcontroller [Diagrams](https://drive.google.com/open?id=1vYwbhqZFr9MfyZ7n4dp7TtP5YDJytpeIPDIbStRjbj4) 
- Source files found on [Github](https://github.com/jovillacorta/csee120b-finalproject) 
 
# Description of Source files:
- joystick.h - initializes joystick ADC
- songData.h - contains song arrays
- variables.h - shared variables in system
- additional header files** (timer.h, scheduler.h, bit.h, pwm.h, io.c, io.h)
- main.c - controls state machine ticks
- menuTick.c - sets menu screen and menu option screens
- songTick.c - iterates through song arrays and sets frequency
- pwm.c - uses PWM functionality to play frequencies on speaker
- scoreIncTick.c - increments score in Play Game mode
- scoreDispTick.c - writes the score to screen in Play Game mode, then blinks score
- creditsTick.c - when in Credits or High Score mode, pressing button returns to menu
- LCD_Tick.c - updates the LCD screen
- arduino.c (code used with Arduino IDE)

***HEADERS PROVIDED BY UCR CS120B*
