#ifndef GBGAME_VIBRATION_H
#define GBGAME_VIBRATION_H

#include <Arduino.h>

class Vibration {

public:
    Vibration(); //set pinMode

    void on(); //set pin high

    void off(); //set pin low
};

#endif 