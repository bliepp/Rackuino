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

	MIDI.begin(MIDI_CHANNEL_IN);//  Only listen to one port
	MIDI.turnThruOff();

#ifdef STARTUP_ANIMATION
	for (uint8_t i = 0; i < 2*N_BUTTONS; i++){
		digitalWrite(LED(i % N_BUTTONS), i < N_BUTTONS);
		delay(STARTUP_ANIMATION_STEP);
	}
#endif
}

void loop() {
	// MIDI OUT
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		buttons[i].update();
		if (buttons[i].fell()){ // PRESSED
			if (!is_toggleable(i)){
				bitSet(toggled_internally, i); // set bit to 1
				MIDI.sendControlChange(INDEX_TO_CC(i), 127, MIDI_CHANNEL);
			} else {
				bitToggle(toggled_internally, i); // invert bit
				MIDI.sendControlChange(INDEX_TO_CC(i), 127*bitRead(toggled_internally, i), MIDI_CHANNEL);
			}
		}
		if (buttons[i].rose()){ // RELEASED
			if (!is_toggleable(i)){
				bitClear(toggled_internally, i); // set bit to 0
				MIDI.sendControlChange(INDEX_TO_CC(i), 0, MIDI_CHANNEL);
			}
		}
	}

	// MIDI IN
	if (MIDI.read()){
		if (MIDI.getType() == midi::ControlChange){
			int16_t cc = CC_TO_INDEX(MIDI.getData1());
			if (cc >= 0 and cc < N_BUTTONS){
				bitWrite(toggled_externally, cc, MIDI.getData2() > 64);
			}
		}
	}

	// SET LEDS
	for (uint8_t i = 0; i < N_BUTTONS; i++)
		digitalWrite(LED(i), bitRead(toggled_internally | toggled_externally, i));
}

//  FUNCTIONS
bool is_toggleable(uint8_t index){
	for (uint8_t i = 0; i < sizeof(toggleable)/sizeof(toggleable[0]); i++){
		if (index == toggleable[i])
			return true;
	}
	return false;
}
