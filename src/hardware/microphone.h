#ifndef GBGAME_MICROPHONE_H
#define GBGAME_MICROPHONE_H

#include <Arduino.h>
#include "PDM.h"

class Microphone {
public:
    Microphone();
   // static Microphone* instance; // Static instance pointer
    void readValue();

    static void onPDMdata(); // Static callback handler

    int value = 0;

private:
    static const int channels = 1;
    static const int frequency = 16000;
    static const int bufferSize = 512;
    static uint16_t sampleBuffer[bufferSize];

    static volatile int samplesRead;
};

#endif // GBGAME_MICROPHONE_H
