#include <Arduino.h>
#include "rtos.h"
#include "hardware/displayManager.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "states/stateHandler.h"
#include "wifi/dataTransmit.h"
#include "functionality/scores.h"
#include "functionality/readWriteFlash.h"
#include "mbed_stats.h"

//#define DEBUG
uint32_t State::instanceCounter = 0; // Static variable to keep track of the number of instances of State
DisplayManager& dm = DisplayManager::getInstance(); // Display manager instance
Buttons button;
StateHandler stateHandler;
Scores &scores = Scores::getInstance();
DataTransmit &wifi = DataTransmit::getInstance();

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
    //Get the Wi-Fi credentials from the flash
    wifi.userName = flash::readFromFlash("username");
    wifi.ssid = flash::readFromFlash("network");
    wifi.password = flash::readFromFlash("password");
}

void loop() {
    using namespace std::chrono;
    rtos::ThisThread::sleep_for(seconds(4));
    print_memory_info();
}