#include "microphone.h"

Microphone* Microphone::instance = nullptr;

uint16_t Microphone::sampleBuffer[Microphone::bufferSize];
volatile int Microphone::samplesRead = 0;

Microphone::Microphone() {
    instance = this;  // Set the instance pointer
    //PDM.onReceive(onPDMdata);

    if (!PDM.begin(channels, frequency)) {
        Serial.println("Failed to start PDM!");
        while (1);
    }

    for (int i = 0; i < bufferSize; i++) {
        sampleBuffer[i] = 0;
    }
}

void Microphone::onPDMdata() {
   // if (instance == nullptr) return;

    // Query the number of available bytes
    int bytesAvailable = PDM.available();

    // Read into the instance's sample buffer
    PDM.read(instance->sampleBuffer, bytesAvailable);

    // Calculate number of samples read
    instance->samplesRead = bytesAvailable / 2;
}


void Microphone::readValue() {
    onPDMdata();
    if (samplesRead) {

        // Print samples to the serial monitor or plotter
        for (int i = 0; i < samplesRead; i++) {
        //Serial.println(sampleBuffer[i]);
            if (sampleBuffer[i] > 10000 || sampleBuffer[i] <= -10000) {
                value++;
                if(value >= 128) {
                value = 128;
                }
            }
            else {
                value--;
                if(value <= -1) {
                value = -1;
                }
            }
        }
    }
}