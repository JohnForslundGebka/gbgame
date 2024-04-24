#include <Arduino.h>
#include <Serial.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"
#include "hardware/buttons.h"
//Buttons object
Buttons buttons;


// Create a DigitalOut object to control the LED
mbed::DigitalOut led(LED1);

// Function that toggles the LED in a thread
void toggleLED() {

    while (true) {
        led = !led;  // Toggle the state of the LED
        rtos::ThisThread::sleep_for(500);  // Sleep for 500 milliseconds
    }
}

//// Main thread object
//rtos::Thread thread;

void setup() {
    // Start the thread, running the toggleLED function
    //thread.start(mbed::callback(toggleLED));

    Serial.begin(9600);
}

void loop() {

    Serial.println(buttons.buttonStates.get());


}