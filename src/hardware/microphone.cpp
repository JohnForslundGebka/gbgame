#include "Microphone.h"

// Initialize static member variables
short Microphone::sampleBuffer[Microphone::bufferSize];
volatile int Microphone::samplesRead = 0;

Microphone::Microphone() {}

void Microphone::init() {

    PDM.onReceive(onPDMdata);

    if (!PDM.begin(channels, frequency)) {
        Serial.println("Failed to start PDM!");
        while (1);
    }

    //PDM.setGain(10);
}

void Microphone::end() {
    PDM.end();
}

void Microphone::processAudioData() {
    if (samplesRead) {

        for (int i = 0; i < samplesRead; i++) {
            
            if (sampleBuffer[i] > 10000 || sampleBuffer[i] <= -10000) {
                m_value++;

                if (m_value > 2) {m_value = 1;}
                //delay(1000);
            }
        }

        m_value--;
        if (m_value < -1) {m_value = -1;}

        samplesRead = 0; // Clear the read count

        // Serial.println(m_value);
    }
    //Serial.println(m_value);
}

void Microphone::onPDMdata() {
    int bytesAvailable = PDM.available();
    PDM.read(sampleBuffer, bytesAvailable);
    samplesRead = bytesAvailable / 2;
}