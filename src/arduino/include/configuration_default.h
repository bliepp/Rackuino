#include <Arduino.h>


// BUTTON SETUP
#define N_BUTTONS 6		// number of buttons, max: half of available digital pins.
#define BUTTON_0 2		// pin of button 0 (where the numbering starts)
#define TOGGLEABLE		// comma seperated list of button numbers, default: no switch is in toggle mode
#define DEBOUNCE_TIME 20 	// softare based debouncing, in ms


// LED SETUP
#define USE_LEDS					// comment if you don't want to use a LED per button
#define STARTUP_ANIMATION			// uncomment if animation not wanted
#define STARTUP_ANIMATION_STEP 100	// duration between each animation step, in ms
#define LED_OFFSET N_BUTTONS		// offset between BUTTON(i) and LED(i), default: N_BUTTONS (button pins directly followed by led pins)


// MIDI SETUP
#define MIDI_CHANNEL 12			// important: channels are 1 based, not 0 based like usually used in programming!
#define MIDI_CHANNEL_IN MIDI_CHANNEL	// use 0 (MIDI_CHANNEL_OMNI) for all channels and > 16 (MIDI_CHANNEL_OFF) to deactivate
#define MIDI_CC_STARTVALUE 102		// CC number which should be triggered by button 0
