#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/displayManager.h"
#include "hardware/buttons.h"
#include "game/stateHandler.h"
#include "game/distanceGame.h"


using namespace mbed;
using namespace rtos;
using namespace std::chrono;

DisplayManager& displayManager = DisplayManager::getInstance();
Buttons button;

DistanceGame distanceGame;

StateHandler stateHandler(distanceGame);

// // Main thread object
// Thread thread;

void setup() {
    Serial.begin(9600);
    displayManager.init();
    stateHandler.run();

    
}

void loop() {
    // int reading = random(1, 100);
    // Serial.println(reading);
    // delay(500);
}