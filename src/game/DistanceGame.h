#ifndef DISTANCEGAME_H
#define DISTANCEGAME_H

#include <Arduino.h>
#include <Serial.h>
#include <SPI.h>
#include "core/macros.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/ultrasonic.h"


class DistanceGame : public State {
private: 
    Thread game;
    Ultrasonic ultrasonic;


public:
    DistanceGame() {};

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

};


#endif