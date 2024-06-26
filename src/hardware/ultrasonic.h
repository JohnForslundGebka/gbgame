//ultrasonic.h

/**
 * @brief This class handles the ultrasonic sensor. 
 *        It initializes the pins to the correct mode and has a method that
 *        reads and returns the distance in centimeters. 
 *
 *        The defined pins gets setup in the constructor.
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include "core/macros.h"


class Ultrasonic {
public:
    Ultrasonic() { init(); }

    void init() {
        pinMode(ECHO_PIN, INPUT); // Sets the TRIG_PIN as an Output
        pinMode(TRIG_PIN, OUTPUT); // Sets the ECHO_PIN as an Input
    }

    int readDistance() {
        unsigned long duration;
        int distance; 

        // Makes sure the TRIG pin is low
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);

        // Set the TRIG pin high for 10 microseconds then low
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        // Reads the ECHO pin, returns the sound travel time in microseconds
        duration = pulseIn(ECHO_PIN, HIGH);

        // Calculates the distance in centimeters
        distance = duration * 0.034 / 2;
        
        // Returns the distance in centimeters
        return distance;
    }

};



#endif  