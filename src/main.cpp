#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"

using namespace mbed;
using namespace rtos;

volatile bool shouldPrint = false;

InterruptIn button(pin::BTN_A,PullUp);
InterruptIn buttonB(pin::BTN_B,PullUp);
Thread thread1;
EventFlags flags;

#define FLAG1 (1UL << 1)
#define FLAG2 (1UL << 2)

void print(){

    while(true) {
        flags.wait_all(FLAG1, osWaitForever, false);
        while (true) {
            if (shouldPrint) {
                Serial.println("ON");
            } else {
                Serial.println("OFF");
            }
            ThisThread::sleep_for(std::chrono::milliseconds(500));
            if (!(flags.get() & FLAG1))
                break;
        }
    }
}

void on_button_press() {
   // shouldPrint = !shouldPrint;
   flags.set(FLAG1);
}

void on_button_press2(){
    flags.clear(FLAG1);
}

void setup() {
    Serial.begin(9600);
    button.fall(&on_button_press);
    buttonB.fall(&on_button_press2);
    thread1.start(print);

}

void loop() {

}