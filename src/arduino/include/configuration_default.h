#include <Arduino.h>

// BUTTON SETUP
#define N_BUTTONS 6		// number of buttons. max: half of available digital pins.
#define BUTTON_0 2		// pin where the numbering starts
#define DEBOUNCE_TIME 20 	// in ms

uint8_t toggleable[] = {};	// default: no switch is in toggle mode


// MIDI SETUP
#define CHANNEL 12 // 13th channel
#define CC_STARTVALUE 102 // CC number which should be triggered by button 0
