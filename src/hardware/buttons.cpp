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

    

    // Initialize all buttons to trigger on both rising and falling edges
    auto callback = mbed::callback(this, &Buttons::handleButtonPressRelease);
    
    
    buttonUp.rise([&]() {buttonStates.clear(UP_FLAG);});
    buttonUp.fall([&]() {buttonStates.set(UP_FLAG);});

//     buttonUp.rise(callback);
//     buttonUp.fall(callback);

//     buttonLeft.rise(callback);
//     buttonLeft.fall(callback);

//     buttonRight.rise(callback);
//     buttonRight.fall(callback);

//     buttonStart.rise(callback);
//     buttonStart.fall(callback);

//     buttonA.rise(callback);
//     buttonA.fall(callback);

//     buttonB.rise(callback);
//     buttonB.fall(callback);

//     buttonDown.rise(callback);
//     buttonDown.fall(callback);
// 
}

void Buttons::handleButtonPressRelease(mbed::InterruptIn &button, uint32_t flag) {
    if (button.read() == 0) {  // Assuming active low buttons
        buttonStates.set(flag);
    } else {
        buttonStates.clear(flag);
    }
    Serial.println("Button state changed.\n");
}







