#include <Arduino.h>
#include <MIDI.h>
#include <localtools.h>


// BUTTON SETUP
#define N_BUTTONS 6
#define BUTTON_0 2

#define BUTTON(no) ((no) + BUTTON_0)
#define LED(no) (BUTTON(no) + N_BUTTONS)

#define PRESSED -1 // new is low, old is high
#define RELEASED 1 // new is high, old is low


// MIDI SETUP
#define CHANNEL 12 // 13th channel
#define CC_NUMBER(no) ((no) + 102)

MIDI_CREATE_DEFAULT_INSTANCE();


// GLOBAL STATE VARIABLES
bool button_state[2][N_BUTTONS]; // 0: new, 1: old
bool toggled[N_BUTTONS];

uint8_t toggleable[] = {0, 3}; // lsit of all buttons which should be toggleable


void setup() {
	//Serial.begin(9600);
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		pinMode(BUTTON(i), INPUT_PULLUP);
		pinMode(LED(i), OUTPUT);
		button_state[0][i] = HIGH;
		button_state[1][i] = HIGH;
		toggled[i] = false;
	}

	MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		button_state[0][i] = digitalRead(BUTTON(i));
		switch (button_state[0][i] - button_state[1][i])
		{
		case RELEASED:
			if (!is_toggleable(i))
				MIDI.sendControlChange(CC_NUMBER(i), 0, CHANNEL);
			//MIDI.sendNoteOff(42, 0, 1);
			//MIDI.sendControlChange(CC_NUMBER(i), 0, MIDI_CHANNEL_OMNI);
			button_state[1][i] = button_state[0][i];
			break;
		case PRESSED:
			if (!is_toggleable(i))
				MIDI.sendControlChange(CC_NUMBER(i), 127, CHANNEL);
			else {
				MIDI.sendControlChange(CC_NUMBER(i), 127*toggled[i], CHANNEL);
				toggled[i] = !toggled[i];
			}
			button_state[1][i] = button_state[0][i];
			break;
		}
	}
}

bool is_toggleable(uint8_t index){
	for (uint8_t i = 0; i < sizeof(toggleable)/sizeof(toggleable[0]); i++){
		if (index == toggleable[i])
			return true;
	}
	return false;
}
