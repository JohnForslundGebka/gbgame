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
#include "functionality/readWriteFlash.h"
#include "mbed_stats.h"
#include "functionality/challengeHandler.h"

#include "hardware/vibration.h"

//#define DEBUG
uint32_t State::instanceCounter = 0;
DisplayManager& dm = DisplayManager::getInstance();
Buttons button;
StateHandler stateHandler;
Scores &scores = Scores::getInstance();
DataTransmit &wifi = DataTransmit::getInstance();
ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();


void print_memory_info() {
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);

    Serial.print("Current heap: ");
    Serial.println(heap_stats.current_size);

    Serial.print("Max heap size: ");
    Serial.println(heap_stats.max_size);

    Serial.print("Total heap size: ");
    Serial.println(heap_stats.reserved_size);

    Serial.print("Alloc count: ");
    Serial.println(heap_stats.alloc_cnt);

    Serial.print("Alloc fail count: ");
    Serial.println(heap_stats.alloc_fail_cnt);
    Serial.println("------------------------------------");
    Serial.println(" ");
}

void setup() {
    Serial.begin(115200);
    dm.init();
    stateHandler.init();
    scores.init();
    wifi.userName = flash::readFromFlash("username");
    wifi.ssid = flash::readFromFlash("network");
    wifi.password = flash::readFromFlash("password");

    
}



void loop() {
    using namespace std::chrono;

    //vibration.on();
    //pinMode(9, OUTPUT);
    //digitalWrite(9, HIGH);
   // Serial.println(wifi.ssid);
    rtos::ThisThread::sleep_for(seconds(4));
    //vibration.off();


}