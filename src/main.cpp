#include <Arduino.h>
#include <Serial.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"
#include "hardware/buttons.h"

//Buttons object
Buttons buttons;
uint32_t flagsRead = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    flagsRead = buttons.buttonStates.wait_any(
            Buttons::UP_FLAG |
            Buttons::LEFT_FLAG |
            Buttons::RIGHT_FLAG |
            Buttons::START_FLAG |
            Buttons::A_FLAG |
            Buttons::B_FLAG |
            Buttons::DOWN_FLAG, osWaitForever, false
    );
    Serial.println(flagsRead);


}