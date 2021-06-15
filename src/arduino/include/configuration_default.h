#include <Arduino.h>

// BUTTON SETUP
#define N_BUTTONS 6		// number of buttons. max: half of available digital pins.
#define BUTTON_0 2		// pin where the numbering starts
#define DEBOUNCE_TIME 10 	// in ms

uint8_t toggleable[] = {0, 1, 3};


// MIDI SETUP
#define CHANNEL 12 // 13th channel
#define CC_NUMBER(no) ((no) + 102)
