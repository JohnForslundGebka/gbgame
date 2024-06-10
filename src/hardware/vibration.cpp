#include "vibration.h"

#define VIB_PIN 9

Vibration::Vibration() {
    pinMode(VIB_PIN, OUTPUT);
    digitalWrite(VIB_PIN, LOW);
}

void Vibration::on() {
    digitalWrite(VIB_PIN, HIGH);
}

void Vibration::off() {
    digitalWrite(VIB_PIN, LOW);
}