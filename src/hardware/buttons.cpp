//buttons.cpp
#include "buttons.h"


Buttons::Buttons()
        : buttonUp(pin::BTN_UP, PullUp),
          buttonLeft(pin::BTN_LEFT, PullUp),
          buttonRight(pin::BTN_RIGHT, PullUp),
          buttonStart(pin::BTN_START, PullUp),
          buttonA(pin::BTN_A, PullUp),
          buttonB(pin::BTN_B, PullUp),
          buttonDown(pin::BTN_DOWN, PullUp)
{
    //callback functions for the buttons
    buttonUp.rise([this]() { buttonStates.clear(UP_FLAG); });
    buttonUp.fall([this]() { buttonStates.set(UP_FLAG); });

    buttonLeft.rise([this]() { buttonStates.clear(LEFT_FLAG); });
    buttonLeft.fall([this]() { buttonStates.set(LEFT_FLAG); });

    buttonRight.rise([this]() { buttonStates.clear(RIGHT_FLAG); });
    buttonRight.fall([this]() { buttonStates.set(RIGHT_FLAG); });

    buttonStart.rise([this]() { buttonStates.clear(START_FLAG); });
    buttonStart.fall([this]() { buttonStates.set(START_FLAG); });

    buttonA.rise([this]() { buttonStates.clear(A_FLAG); });
    buttonA.fall([this]() { buttonStates.set(A_FLAG); });

    buttonB.rise([this]() { buttonStates.clear(B_FLAG); });
    buttonB.fall([this]() { buttonStates.set(B_FLAG); });

    buttonDown.rise([this]() { buttonStates.clear(DOWN_FLAG); });
    buttonDown.fall([this]() { buttonStates.set(DOWN_FLAG); });
}








