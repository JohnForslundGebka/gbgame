#include "Microphone.h"

// Initialize static member variables
short Microphone::sampleBuffer[Microphone::bufferSize];
volatile int Microphone::samplesRead = 0;

Microphone::Microphone() {}

void Microphone::init() {
    Serial.begin(9600);
    while (!Serial);

    PDM.onReceive(onPDMdata);

    if (!PDM.begin(channels, frequency)) {
        Serial.println("Failed to start PDM!");
        while (1);
    }
}

void Microphone::processAudioData() {
    if (samplesRead) {

        for (int i = 0; i < samplesRead; i++) {
            
            if (sampleBuffer[i] > 10000 || sampleBuffer[i] <= -10000) {
                value++;
                if (value > 2) {value = 1;}
                //delay(1000);
            }
        }

        value--;
        if (value < -1) {value = -1;}

        samplesRead = 0; // Clear the read count
    }
}

void Microphone::onPDMdata() {
    int bytesAvailable = PDM.available();
    PDM.read(sampleBuffer, bytesAvailable);
    samplesRead = bytesAvailable / 2;
}
