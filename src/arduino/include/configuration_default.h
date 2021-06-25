#include <Arduino.h>


// BUTTON SETUP
#define N_BUTTONS 6		// number of buttons, max: half of available digital pins except TX/RX, if no LEDs are used.
#define BUTTON_0 2		// pin of button 0 (where the numbering starts)
#define TOGGLEABLE		// comma seperated list of button numbers (starts with 0), default: empty (all in momentary mode, none in toggle mode)
#define DEBOUNCE_TIME 20 	// software based debouncing, in ms, default: 20 (enough for most arcade like switches)


// LED SETUP
#define USE_LEDS			// comment if you don't want to use one LED per button
#define STARTUP_ANIMATION		// comment if you don't want an LED animation on powering
#define STARTUP_ANIMATION_STEP 100	// duration between each animation step, in ms, default 100
#define LED_OFFSET N_BUTTONS		// offset between BUTTON(i) and LED(i), default: N_BUTTONS (button pins directly followed by led pins)


// MIDI SETUP
#define MIDI_CHANNEL 12			// important: channels are 1 based, not 0 based like usually used in programming!
#define MIDI_CHANNEL_IN MIDI_CHANNEL	// use 0 (MIDI_CHANNEL_OMNI) for all channels and > 16 (MIDI_CHANNEL_OFF) to deactivate
#define MIDI_CC_STARTVALUE 102		// CC number which should be triggered by button 0
