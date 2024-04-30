#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include <Serial.h>

#include "hardware/ultrasonic.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;



Ultrasonic ultrasonic;

void setup() {
    Serial.begin(9600);
}


void loop() {
    int measurment = ultrasonic.readDistance();

    Serial.println(measurment);

    delay(400);
}