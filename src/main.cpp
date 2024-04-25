#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Serial.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/buttons.h"

using namespace mbed;
using namespace rtos;

//Buttons object
Buttons buttons;


void setup() {
    Serial.begin(9600);
}

void loop() {
    //Wait for any of ALL_flags to be set.
    switch (buttons.states.wait_any(Buttons::ALL_FLAG)) {
        case Buttons::UP_FLAG:
            Serial.println("Button UP");
            break;
        case Buttons::LEFT_FLAG:
            Serial.println("Button LEFT");
            break;
        case Buttons::RIGHT_FLAG:
            Serial.println("Button RIGHT");
            break;
        case Buttons::DOWN_FLAG:
            Serial.println("Button DOWN");
            break;
        case Buttons::A_FLAG:
            Serial.println("Button A");
            break;
        case Buttons::B_FLAG:
            Serial.println("Button B");
            break;
        case Buttons::START_FLAG:
            Serial.println("Button START");
            break;
        default:
            break;
    }

    
}