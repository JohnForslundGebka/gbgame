#include <Arduino.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/displayManager.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "states/mainMenu/mainMenu.h"
#include "states/stateHandler.h"

#include "mbed_stats.h"

//#define DEBUG
using namespace mbed;
using namespace rtos;
using namespace std::chrono;

uint32_t State::instanceCounter = 0;
DisplayManager& dm = DisplayManager::getInstance();
Buttons button;
StateHandler stateHandler;

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

//    // Stack statistics (aggregated)
//    mbed_stats_stack_t stack_stats;
//    mbed_stats_stack_get(&stack_stats);
//    Serial.println("Stack Statistics:");
//    Serial.print("Max stack size used: ");
//    Serial.println(stack_stats.max_size);
//    Serial.print("Reserved stack size: ");
//    Serial.println(stack_stats.reserved_size);

//    // Thread statistics
//    mbed_stats_thread_t thread_stats[MBED_CONF_RTOS_THREAD_STACK_SIZE];
//    size_t num_threads = mbed_stats_thread_get_each(thread_stats, MBED_CONF_RTOS_THREAD_STACK_SIZE);
//    Serial.println("Thread Statistics:");
//    for (size_t i = 0; i < num_threads; i++) {
//        Serial.print("Thread ID: ");
//        Serial.println(thread_stats[i].id);
//        Serial.print("State: ");
//        Serial.println(thread_stats[i].state);
//        Serial.print("Priority: ");
//        Serial.println(thread_stats[i].priority);
//        Serial.print("Stack Size: ");
//        Serial.println(thread_stats[i].stack_size);
//        Serial.print("Stack Space: ");
//        Serial.println(thread_stats[i].stack_space);
//        Serial.print("Name: ");
//        if (thread_stats[i].name) {
//            Serial.println(thread_stats[i].name);
//        } else {
//            Serial.println("N/A");
//        }
//    }
}


void setup() {
    Serial.begin(115200);
    dm.init();
    stateHandler.init();
    delay(1000);

}

void loop() {
   ThisThread::sleep_for(seconds(2));
    print_memory_info();
}