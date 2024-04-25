//buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"

using namespace mbed;
using namespace rtos;

 class Buttons {
public:
    Buttons();  // Constructor to initialize all buttons
    
    // Event flags for button states
    static EventFlags buttonStates;
    enum ButtonFlags {
        UP_FLAG = 0x01,
        LEFT_FLAG = 0x02,
        RIGHT_FLAG = 0x04,
        START_FLAG = 0x08,
        A_FLAG = 0x10,
        B_FLAG = 0x20,
        DOWN_FLAG = 0x40,
        UP_RIGHT_FLAG = UP_FLAG | RIGHT_FLAG,
        UP_LEFT_FLAG = UP_FLAG | LEFT_FLAG,
        DOWN_LEFT_FLAG = DOWN_FLAG | LEFT_FLAG,
        DOWN_RIGHT_FLAG = DOWN_FLAG | RIGHT_FLAG,
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