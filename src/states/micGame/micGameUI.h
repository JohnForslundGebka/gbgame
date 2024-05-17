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

    void drawWaveform();
    void updateWave();

    void drawBall(int pos);


private:
    static const int size = 128;
    int arr[size];  // Waveform data
    int lastXValue = 0;  // Last value for generating the next point
    float frequency = 0.1;  // Initial frequency of the sine wave
    float amplitude = 20;   // Initial amplitude of the sine wave
};

#endif //GBGAME_MIC_GAMEUI_H
