//buttons.cpp
#include "buttons.h"


Buttons::Buttons()
    : buttonUp(pin::BTN_UP, PullUp),
      buttonLeft(pin::BTN_LEFT, PullUp),
      buttonRight(pin::BTN_RIGHT, PullUp),
      buttonStart(pin::BTN_START, PullUp),
      buttonA(pin::BTN_A, PullUp),
      buttonB(pin::BTN_B, PullUp),
      buttonDown(pin::BTN_DOWN, PullUp) {

  

    buttonUp.rise([&]() {buttonStates.clear(UP_FLAG);});
    buttonUp.fall([&]() {buttonStates.set(UP_FLAG);});

    buttonLeft.rise([&]() {buttonStates.clear(LEFT_FLAG);});
    buttonLeft.fall([&]() {buttonStates.set(LEFT_FLAG);});

    buttonRight.rise([&]() {buttonStates.clear(RIGHT_FLAG);});
    buttonRight.fall([&]() {buttonStates.set(RIGHT_FLAG);});

    buttonStart.rise([&]() {buttonStates.clear(START_FLAG);});
    buttonStart.fall([&]() {buttonStates.set(START_FLAG);});

    buttonA.rise([&]() {buttonStates.clear(A_FLAG);});
    buttonA.fall([&]() {buttonStates.set(A_FLAG);});

    buttonB.rise([&]() {buttonStates.clear(B_FLAG);});
    buttonB.fall([&]() {buttonStates.set(B_FLAG);});

    buttonDown.rise([&]() {buttonStates.clear(DOWN_FLAG);});
    buttonDown.fall([&]() {buttonStates.set(DOWN_FLAG);});

}


void Buttons::printBinaryStates() {
    // Assuming you want to display 19 bits as per your example
    std::bitset<7> bitRep(buttonStates.get());
    Serial.println(bitRep.to_string().c_str()); // Convert bitset to string and print
}


void Buttons::handleButtonPressRelease(mbed::InterruptIn &button, uint32_t flag) {
    if (button.read() == 0) {  // Assuming active low buttons
        buttonStates.set(flag);
    } else {
        buttonStates.clear(flag);
    }
    Serial.println("Button state changed.\n");
}







