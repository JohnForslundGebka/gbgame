//vibration.h

/**
 * @brief This class handles the vibration motor. It sets up the correct pin and pinMode 
 * in the constructor and contains two simple function for turning the vibration motor on or off. 
 */

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