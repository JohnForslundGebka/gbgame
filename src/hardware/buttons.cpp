//buttons.cpp
#include "buttons.h"

rtos::EventFlags Buttons::states;

Buttons::Buttons()
    : buttonUp(pin::BTN_UP, PullUp),
      buttonLeft(pin::BTN_LEFT, PullUp),
      buttonRight(pin::BTN_RIGHT, PullUp),
      buttonStart(pin::BTN_START, PullUp),
      buttonA(pin::BTN_A, PullUp),
      buttonB(pin::BTN_B, PullUp),
      buttonDown(pin::BTN_DOWN, PullUp) {

  
    // Sets the button state flags for each interrupt
    buttonUp.rise([&]() {states.clear(UP_FLAG);});
    buttonUp.fall([&]() {states.set(UP_FLAG);});

    buttonLeft.rise([&]() {states.clear(LEFT_FLAG);});
    buttonLeft.fall([&]() {states.set(LEFT_FLAG);});

    buttonRight.rise([&]() {states.clear(RIGHT_FLAG);});
    buttonRight.fall([&]() {states.set(RIGHT_FLAG);});

    buttonStart.rise([&]() {states.clear(START_FLAG);});
    buttonStart.fall([&]() {states.set(START_FLAG);});

    buttonA.rise([&]() {states.clear(A_FLAG);});
    buttonA.fall([&]() {states.set(A_FLAG);});

    buttonB.rise([&]() {states.clear(B_FLAG);});
    buttonB.fall([&]() {states.set(B_FLAG);});

    buttonDown.rise([&]() {states.clear(DOWN_FLAG);});
    buttonDown.fall([&]() {states.set(DOWN_FLAG);});

}

//Prints out the states variable in binary form for debugging
void Buttons::printBinaryStates() {
    std::bitset<7> bits(states.get()); // Show 7 bits
    Serial.println(bits.to_string().c_str()); // Convert bitset to string and print
}








