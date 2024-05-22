#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/displayManager.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "states/mainMenu/mainMenu.h"
#include "states/stateHandler.h"
#include "mbed_stats.h"

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

//#define DEBUG
//char m_username[5] = {'A', 'A', 'A', 'A', '\0'};


uint32_t State::instanceCounter = 0;
DisplayManager& dm = DisplayManager::getInstance();
Buttons button;
StateHandler stateHandler;





void setup() {
    Serial.begin(115200);
    dm.init();
    stateHandler.init();
}

void loop() {
    using namespace std::chrono;
    //print_memory_info();
    rtos::ThisThread::sleep_for(seconds(3));

}