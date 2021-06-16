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
#define BUTTON(no) ((no) + BUTTON_0)
#define LED(no) (BUTTON(no) + N_BUTTONS)


// MIDI SETUP
#define CC_NUMBER(no) ((no) + CC_STARTVALUE)


// GLOBAL VARIABLES
Bounce buttons[N_BUTTONS];
uint32_t toggled = 0; // 8 should enough but safe is safe -> int can be described as array of bits/bools, so 32 buttons possible

#endif // SETUP_H
