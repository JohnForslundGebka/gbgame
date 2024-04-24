#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"

mbed::DigitalIn knapp(pin::BTN_A , PullUp);
mbed::DigitalOut vibration(pin::VIBRA);

// Create a DigitalOut object to control the LED
mbed::DigitalOut led(LED1);

// Function that toggles the LED in a thread
void toggleLED() {

    while (true) {
        led = !led;  // Toggle the state of the LED
        rtos::ThisThread::sleep_for(500);  // Sleep for 500 milliseconds
    }
}

// Main thread object
rtos::Thread thread;

void setup() {
    // Start the thread, running the toggleLED function
    thread.start(mbed::callback(toggleLED));
}

void loop() {

    if(!knapp.read())
        vibration = !vibration;



}