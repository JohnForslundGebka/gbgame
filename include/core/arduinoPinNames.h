//this headerfile contains the PinName variables for the digital pins on the Aruino Nano rp2040 connect
//
//  Usage:   pin::BTN_UP
//


#ifndef GBGAME_ARDUINOPINNAMES_H
#define GBGAME_ARDUINOPINNAMES_H


namespace pin {
    //These are the pins the buttons and vibration motor is connected to.
    constexpr PinName BTN_UP = p25;    // D2 is p25
    constexpr PinName BTN_LEFT = p15;  // D3 is p15
    constexpr PinName BTN_RIGHT = p16; // D4 is p16
    constexpr PinName BTN_START = p17; // D5 is p17
    constexpr PinName BTN_A = p18;
    constexpr PinName BTN_B = p19;     // D7 is p19
    constexpr PinName BTN_DOWN = p20;  // D8 is p20
    constexpr PinName VIBRA = p21;     // D9 is p21
}

#endif //GBGAME_ARDUINOPINNAMES_H
