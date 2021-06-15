#include <Arduino.h>
#if __has_include("configuration.h")
#	include <configuration.h>
#else
#	include <configuration_default.h>
#endif

// BUTTON SETUP
#define BUTTON(no) ((no) + BUTTON_0)
#define LED(no) (BUTTON(no) + N_BUTTONS)

#define STATE_CHANGED(arr) (arr)[0][i]
#define PRESSED -1 // new is low, old is high
#define RELEASED 1 // new is high, old is low
#define DEBOUNCE_TIME 10


// GLOBAL VARIABLES
bool button_state[N_BUTTONS][2]; // 0: new, 1: old
uint16_t toggled = 0; // 8 should enough but safe is safe -> int canbe described as array of bits/bools


// FUNCTIONS
bool is_toggleable(uint8_t index){
	for (uint8_t i = 0; i < sizeof(toggleable)/sizeof(toggleable[0]); i++){
		if (index == toggleable[i])
			return true;
	}
	return false;
}
