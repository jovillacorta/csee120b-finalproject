#ifndef _SONG_TICK_
#define _SONG_TICK_

#include "variables.h"
#include "songData.h"

enum song_states {song_INIT, song_WAIT, song_COUNTDOWN, song_SOUND};

double noteFrequency = 0;
unsigned char noteIndex = 0;
unsigned char durationCount = 0;

int songTick(int state){
	unsigned char threeSeconds = 68;
	switch(state){
		//-----------------------STATE TRANSITIONS--------------------------
		case song_INIT:
		state = song_WAIT;
		break;
		case song_WAIT: // waits for game to start
		state = (startGame == 0x01) ? song_COUNTDOWN : song_WAIT;
		break;
		case song_COUNTDOWN: // waits until countdown screen is over
		if (i > threeSeconds){
			i = 0;
			state = song_SOUND;
		}
		else state = song_COUNTDOWN;
		break;
		case song_SOUND:  // plays music by iterating through arrays
		if (durationCount > arrayDuration[noteIndex]){
			if (noteIndex >= indexMax){
				endSong = 0x01;
				startGame = 0x00;
				state = song_INIT;
			}
			else {
				noteIndex++;
				durationCount = 0;
				state = song_SOUND;
			}
		}
		else {
			state = song_SOUND;
		}
		break;
		default:
		state = song_INIT;
		break;
	}
	switch(state){
		//-----------------------STATE ACTIONS--------------------------
		case song_INIT:
		durationCount = 0;
		noteIndex = 0;
		noteFrequency = 0;
		endSong = 1;
		break;
		case song_WAIT:
		break;
		case song_COUNTDOWN:
		i++;
		break;
		case song_SOUND:
		durationCount++;
		noteFrequency = arrayNotes[noteIndex];
		break;
		default:
		break;
	}
	return state;
}
#endif