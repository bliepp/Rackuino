#include <Rackuino.h>
#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();


// PROTOTYPES
bool is_toggleable(uint8_t index);

// ARDUINOS MAIN FUNCTIONS
void setup() {
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		buttons[i].attach(BUTTON(i), INPUT_PULLUP);
		buttons[i].interval(DEBOUNCE_TIME);

		pinMode(LED(i), OUTPUT);
	}

	MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		buttons[i].update();
		// MIDI OUT
		if (buttons[i].fell()){ // RELEASED
			if (!is_toggleable(i)){
				MIDI.sendControlChange(CC_NUMBER(i), 127, CHANNEL);
				bitSet(toggled, i); // set bit to 1
			} else {
				MIDI.sendControlChange(CC_NUMBER(i), 127*bitRead(toggled, i), CHANNEL);
				bitToggle(toggled, i); // invert bit
			}
		}
		if (buttons[i].rose()){ // PRESSED
			if (!is_toggleable(i)){
				MIDI.sendControlChange(CC_NUMBER(i), 0, CHANNEL);
				bitClear(toggled, i); // set bit to 0
			}
		}
		// TODO: MIDI IN

		// SET LEDS
		digitalWrite(LED(i), bitRead(toggled, i));
	}
}

//  FUNCTIONS
bool is_toggleable(uint8_t index){
	for (uint8_t i = 0; i < sizeof(toggleable)/sizeof(toggleable[0]); i++){
		if (index == toggleable[i])
			return true;
	}
	return false;
}
