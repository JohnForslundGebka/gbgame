//buttons.h
/**
 * @brief This class handles button and button presses. 
 *        It sets all button pins to be an iterrupt on both falling and rising edges and sets
 *        flags in an EventFlags object according to button state. 
 * 
 *
 * @param states This object holds the current state of each button. 
 *               When an interrupt is triggered it sets the corresponding flag to the button state.
 * @param buttonFlags Enums for each button state flag, this can be expanding .
 * 
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"
#include <bitset>


using namespace mbed;
using namespace rtos;

class Buttons {
public:
    Buttons();  // Constructor to initialize all buttons

    // EventFlags object for button states
    EventFlags states;

    //Enums for flag names
    enum ButtonFlags {
        UP_FLAG = 0x01,
        LEFT_FLAG = 0x02,
        RIGHT_FLAG = 0x04,
        START_FLAG = 0x40,
        A_FLAG = 0x10,
        B_FLAG = 0x20,
        DOWN_FLAG = 0x08,
        ALL_FLAG = (UP_FLAG | LEFT_FLAG | RIGHT_FLAG | START_FLAG | A_FLAG | B_FLAG | DOWN_FLAG)
    };

    //Prints the button states in binary form for debugging
    void printBinaryStates();

private:
  
    // InterruptIn object for each button
    InterruptIn buttonUp;
    InterruptIn buttonLeft;
    InterruptIn buttonRight;
    InterruptIn buttonStart;
    InterruptIn buttonA;
    InterruptIn buttonB;
    InterruptIn buttonDown;
    
};





#endif