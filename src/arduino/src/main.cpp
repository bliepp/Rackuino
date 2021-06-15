#include <Arduino.h>
#include <MIDI.h>

#include <setup.h>


MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		pinMode(BUTTON(i), INPUT_PULLUP);
		pinMode(LED(i), OUTPUT);
		button_state[i][0] = HIGH;
		button_state[i][1] = HIGH;
	}

	MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
	for (uint8_t i = 0; i < N_BUTTONS; i++){
		button_state[i][0] = digitalRead(BUTTON(i));
		switch (STATE_CHANGED(button_state[i]))
		{
		case RELEASED:
			if (!is_toggleable(i))
				MIDI.sendControlChange(CC_NUMBER(i), 0, CHANNEL);
			button_state[i][1] = button_state[i][0];
			delay(DEBOUNCE_TIME); // I know, it's bad. But this is the easiest solution. This is not about time critical buttons.
			break;
		case PRESSED:
			if (!is_toggleable(i)){
				MIDI.sendControlChange(CC_NUMBER(i), 127, CHANNEL);
			} else {
				MIDI.sendControlChange(CC_NUMBER(i), 127*bitRead(toggled, i), CHANNEL);
				bitToggle(toggled, i);
			}
			button_state[i][1] = button_state[i][0];
			delay(DEBOUNCE_TIME);
			break;
		}
	}
}
