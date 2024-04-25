//buttons.h
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
        DOWN_FLAG = 0x08
    };

    //Prints the buttonStates in binary
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