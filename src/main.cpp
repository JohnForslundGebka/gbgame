#include <Arduino.h>
#include "mbed.h"
//#include "rtos.h"
#include "hardware/buttons.h"
#include "states/stateHandler.h"
#include "hardware/displayManager.h"

//#define DEBUG
using namespace mbed;
using namespace rtos;
using namespace std::chrono;

DisplayManager& dm = DisplayManager::getInstance();
Buttons button;
StateHandler stateHandler;

void setup() {
    dm.init();
    stateHandler.init();
}

void loop() {
   ThisThread::sleep_for(seconds(5));
}