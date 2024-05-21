#ifndef GBGAME_MIC_GAMEUI_H
#define GBGAME_MIC_GAMEUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare DistanceGame

class MicGame; // Forward declaration

class MicGameUI {
public:

    explicit MicGameUI(MicGame *pGame);

    MicGame *parentState;
    Canvas c_main;

    void init();

    void drawWaveform();    // Draw waveform from the waveform array
    void updateWave();      // Generates and add the next value in the waveform array and shifts the array values

    bool isWaveformInCircle(int circleX, int circleY, int radius); //checks if the waveform crosses the circle
    
    void drawScreen3();           // Draws the exit/finish screen

    int m_lastBallPos;           //Variable used locally to update correctly
    int m_lastScore = 0;         //Variable used locally to update correctly

private:
    static const int size = 128;       // Audio buffer size
    int arr[size];                     // Waveform data
    int lastXValue = 0;                // Last value for generating the next point
    float frequency = 0.1;             // Initial frequency of the waveform
    float amplitude = 20;              // Initial amplitude of the waveform
};

#endif //GBGAME_MIC_GAMEUI_H
