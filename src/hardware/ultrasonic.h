//ultrasonic.h

/**
 * @brief This class handles button and button presses. 
 *        It sets all button pins to be an iterrupt on both falling and rising edges and sets
 *        flags in an EventFlags object according to button state. 
 * 
 *
 * @param states This object holds the current state of each button. 
 *               When an interrupt is triggered it sets the corresponding flag to the button state.
 * @param buttonFlags Enums for each button state flag, this can be expanding .
 * 
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

//Pins used by the ultrasonic sensor
#define ECHO_PIN 16    //D16
#define TRIG_PIN 17    //D17

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

        // Reads the ECHO pin, returns the sound wave travel time in microseconds
        duration = pulseIn(ECHO_PIN, HIGH);

        // Calculates the distance in centimeters
        distance = duration * 0.034 / 2;
        
        // Returns the distance in centimeters
        return distance;
    }

};



#endif  