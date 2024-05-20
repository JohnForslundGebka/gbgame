#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <Arduino.h>
#include <PDM.h>

class Microphone {
public:
    Microphone();
    void init();
    void processAudioData();
    static void onPDMdata();
    int m_value = 0;

private:
    static const int channels = 1;
    static const int frequency = 16000;
    static const int bufferSize = 512;
    static short sampleBuffer[bufferSize];
    static volatile int samplesRead;
 
};

#endif // MICROPHONE_H
