#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <Bounce2.h>
#if __has_include("configuration.h")
#	include <configuration.h>
#else
#	include <configuration_default.h>
#endif


// HELPERS MISSING IN ARDUINO_H
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))


// BUTTON SETUP
#define BUTTON(index) ((index) + BUTTON_0)


// LED SETUP
#define LED(index) (BUTTON(index) + LED_OFFSET)


// MIDI SETUP
#define INDEX_TO_CC(index) ((index) + MIDI_CC_STARTVALUE)
#define CC_TO_INDEX(cc) ((cc) - MIDI_CC_STARTVALUE)


// GLOBAL VARIABLES
Bounce buttons[N_BUTTONS];
uint8_t toggleable[] = {TOGGLEABLE};
uint32_t toggled_internally = 0;	// 8 should enough but safe is safe, int can be seen
uint32_t toggled_externally = 0;	// as array of bits/bools, so 32 buttons possible

#endif // SETUP_H
