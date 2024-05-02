#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/displayManager.h"
#include "hardware/buttons.h"
#include "game/stateHandler.h"
#include "game/mainMenu.h"


using namespace mbed;
using namespace rtos;
using namespace std::chrono;

DisplayManager& dm = DisplayManager::getInstance();
Buttons button;

// Main thread object
Thread thread;

void setup() {
    dm.init();
}

void loop() {

}