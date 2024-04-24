//buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "DebounceIn.h"
#include "core/arduinoPinNames.h"

using namespace mbed;
using namespace rtos;

class Buttons {
public:
    Buttons();  // Constructor to initialize all buttons
    
    // Event flags for button states
    EventFlags buttonStates;
    enum ButtonFlags {
        UP_FLAG = 0x01,
        LEFT_FLAG = 0x02,
        RIGHT_FLAG = 0x04,
        START_FLAG = 0x08,
        A_FLAG = 0x10,
        B_FLAG = 0x20,
        DOWN_FLAG = 0x40
    };

private:
    // Declare InterruptIn object for each button
    InterruptIn buttonUp;
    InterruptIn buttonLeft;
    InterruptIn buttonRight;
    InterruptIn buttonStart;
    InterruptIn buttonA;
    InterruptIn buttonB;
    InterruptIn buttonDown;
};
#endif