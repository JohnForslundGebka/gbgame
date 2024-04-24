#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "core/arduinoPinNames.h"

using namespace mbed;
using namespace rtos;

InterruptIn button(pin::BTN_A,PullUp);
InterruptIn buttonB(pin::BTN_B,PullUp);
Thread thread1;
EventFlags flags;

#define FLAG1 (1UL << 1)
#define FLAG2 (1UL << 2)
#define FLAG3 (1UL << 3)
#define FLAG4 (1UL << 4)

void print(){



    while(flags.wait_any(FLAG1 | FLAG2 | FLAG3 | FLAG4, osWaitForever,false)) {
       switch (flags.get())
       {
           case FLAG1 :
               Serial.println("SAK 1");
               flags.clear();
               break;
           case FLAG2:
               Serial.println("SAK 2");
               flags.clear();
               break;
           case FLAG3:
               Serial.println("SAK 3");
               flags.clear();
               break;
           case FLAG4:
               Serial.println("SAK 4");
               flags.clear();
               break;
           default:
               break;
       }
      //  ThisThread::sleep_for(std::chrono::milliseconds(500));
    }
}

void on_button_press() {
   flags.set(FLAG1);
}

void on_button_press2(){
    flags.set(FLAG2);
}

void setup() {
    Serial.begin(9600);
    button.fall(&on_button_press);
    buttonB.fall(&on_button_press2);
    thread1.start(print);
}

void loop() {

}