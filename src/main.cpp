#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Create a DigitalOut object to control the LED
DigitalOut led(LED1);

// Function that toggles the LED in a thread
void toggleLED() {

    while (true) {
        led = !led;  // Toggle the state of the LED
        ThisThread::sleep_for(milliseconds(500));
    }
}

// Main thread object
rtos::Thread thread;

void setup() {
    // Start the thread, running the toggleLED function
    thread.start(mbed::callback(toggleLED));
}

void loop() {

}