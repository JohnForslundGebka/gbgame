#include "micGameUI.h"
#include "micGame.h"

MicGameUI::MicGameUI(MicGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
    randomSeed(static_cast<int>(millis()));  // Seed the RNG

        // Generate initial waveform
    for (int i = 0; i < size; ++i) {
        // Sine wave over one full cycle
        arr[i] = 128 / 2 + (sin(i * 2 * PI / size) * (128 / 4));
    }
}

void MicGameUI::init() {}

void MicGameUI::drawWaveform() {
    c_main.C.fillScreen(BLACK);
    // for (int i = 1; i < size; ++i) {
    //     c_main.C.drawLine(i - 1, arr[i - 1], i, arr[i], BLACK);
    // }

    updateWave();
        // Draw the waveform from the array
    for (int i = 1; i < size; ++i) {
        c_main.C.drawLine(i - 1, arr[i - 1], i, arr[i], WHITE);
    }
    // c_main.C.print(parentState->m_testNumber);
}

void MicGameUI::updateWave() {
    // Optionally adjust frequency and amplitude randomly every 'n' updates
    static int updateCount = 0;
    if (updateCount++ % 80 == 0) { // Change frequency and amplitude every 50 frames
        // Random frequency between 0.05 and 0.2 cycles per pixel
        //frequency = random(1, 3) / 100.0; 
        frequency = random(1, 3); 
        // Random amplitude between 10 and 30 pixels
        amplitude = random(1, 30);
    }

    // Shift all values to the left
    for (int i = 0; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    // Calculate new value for the new end point with random frequency and amplitude
    arr[size - 1] = 128 / 2 + int(sin(2 * PI * frequency * lastXValue / size) * amplitude);
    lastXValue++;

    if (lastXValue >= size) {
        lastXValue = 0; // Reset phase if needed
    }
}

void MicGameUI::drawBall(int pos) {

}