#ifndef BUTTONS2_H
#define BUTTONS2_H

#include <Arduino.h>

class Buttons2 {
public:
    static void begin(); // Setup function to initialize pins and attach interrupts
    static bool getButtonState(int index); // Method to access the state of a specific button or knob
    uint8_t getButtonNumber();
    void noButtonsPressed();
    static const uint8_t numberOfButtons = 7;
    //static volatile bool states[numberOfButtons]; // Volatile array to store button and knob states

private:
    //static const uint8_t numberOfButtons = 7;
    static const uint8_t buttonPins[numberOfButtons]; // Array to hold button pin numbers
   static volatile bool states[numberOfButtons]; // Volatile array to store button and knob states

    // Static ISR handlers for each button
    static void ISRButton0();
    static void ISRButton1();
    static void ISRButton2();
    static void ISRButton3();
    static void ISRButton4();
    static void ISRButton5();
    static void ISRButton6();
};

#endif