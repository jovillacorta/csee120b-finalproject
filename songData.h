#ifndef _SONG_DATA_H_
#define _SONG_DATA_H_
//sources:
//SHEET MUSIC REFERENCED FOR ARRAYs: https://musescore.com/bomb_and_kou/shelter 

#define C5 523.25
#define D5 587.33
#define E5 659.25
#define F5 698.46
#define G5 783.99
#define A5 880.00
#define B5 987.77
#define C6 1046.50
#define rest 0.00 // frequencies

const unsigned char indexMax = 74;
double arrayNotes[75] = {C5, rest, A5, G5, C5, rest,
	C5, rest, A5, G5, D5, rest,
	D5, C5, rest, C5, rest, A5, G5, C5, E5, rest,
	E5, C5, D5, rest, E5, C5, D5, rest,
	E5, C5, D5, rest, E5, C5, D5, C5, rest,
	A5, G5, C5, rest, C5, rest, A5, G5, D5, rest,
	E5, G5, rest,
	G5, rest, A5, G5, C5, E5, rest,
	E5, C5, D5, rest, E5, C5, D5, rest,
	E5, C5, D5, rest, E5, C5, D5, C5 
}; //Notes in order
unsigned char arrayDuration[75] = {16, 1, 4, 8, 36, 1,
	16, 1, 4, 8, 16, 1,
	8, 8, 1, 16, 1, 4, 8, 28, 8, 1,
	4, 4, 4, 1, 4, 4, 4, 1,
	4, 4, 4, 1, 4, 4, 4, 16, 1,
	4, 8, 36, 1, 16, 1, 4, 8, 16, 1,
	8, 8, 1,
	16, 1, 4, 8, 28, 8, 1,
	4, 4, 4, 1, 4, 4, 4, 1,
	4, 4, 4, 1, 4, 4, 8, 32
};/* Duration of notes: 16 ticks=quarter note, 8 ticks=eighth note,
  					4 ticks=sixteenth note, rest is always 1 tick
  					(tempo based on period) */