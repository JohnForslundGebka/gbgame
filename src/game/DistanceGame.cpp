#include "DistanceGame.h"

void DistanceGame::DistanceGame() {}

void DistanceGame::handleInput() {
    while (Buttons::states.wait_any(Buttons::A_FLAG, osWaitForever, false)) {
        Serial.println(ultrasonic.readDistance());
    }
}

void DistanceGame::