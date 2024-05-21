
/**
 * @brief This class handles the microphone on the nano RP2040 board.
 * 
 * @class Microphone contains the logic and initializes 
 *        necessary library for reading the microphone.
 *
 */


#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <Arduino.h>
#include <PDM.h>

class Microphone {
public:
    Microphone();
    void init();                //initializes the PDM.h library and sets up ISR.
    void end();
    void processAudioData();    //Returns -1 when no or low sound, returns 0-1 when recieving sound
    static void onPDMdata();    //ISR function that write to the audio buffer        
    
    int m_value = 0;            //Value representing weather mic is recieving sound or not.
                                // -1 when no sound, 1-2 when recieving sound. 

private:
    //Variables for initializing and setting library functions
    static const int channels = 1;
    static const int frequency = 16000;
    static const int bufferSize = 512;
    static short sampleBuffer[bufferSize];
    static volatile int samplesRead;
 
};

#endif // MICROPHONE_H
