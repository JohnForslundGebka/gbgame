#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/displayManager.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "states/mainMenu/mainMenu.h"
#include "states/stateHandler.h"
#include "core/settings.h"
#include "wifi/dataTransmit.h"
#include "functionality/scores.h"

//#define DEBUG
uint32_t State::instanceCounter = 0;
DisplayManager& dm = DisplayManager::getInstance();
Buttons button;
StateHandler stateHandler;
Scores &scores = Scores::getInstance();
DataTransmit &wifi = DataTransmit::getInstance();


void setup() {
    Serial.begin(115200);
    dm.init();
    stateHandler.init();
    scores.init();
    wifi.init();
    delay(500);
    scores.getLeaderboardFromDatabase();
}

void loop() {
    using namespace std::chrono;
    rtos::ThisThread::sleep_for(seconds(3));
}