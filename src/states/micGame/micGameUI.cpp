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

void MicGameUI::init() { m_lastScore = 0; }

void MicGameUI::drawWaveform() {

    //If score changed, print new score
    if(m_lastScore == 0 || m_lastScore != parentState->m_score) {
        c_main.C.fillRect(60, 1, 128, 20, BLACK);
        c_main.C.setTextColor(0xFABF);
        c_main.C.setTextSize(2);
        c_main.C.setTextWrap(false);
        c_main.C.setCursor(5, 3);
        c_main.C.print("Score:");
        c_main.C.setCursor(75, 3);
        c_main.C.print(parentState->m_score);

        //Save last score
        m_lastScore = parentState->m_score;
    }


    // Draw the previous waveform black, ereasing the last frame
    for (int i = 1; i < size; ++i) {
        c_main.C.drawLine(i - 1, arr[i - 1], i, arr[i], BLACK);
    }

    //Calculate new value from the waveform
    updateWave();  

    // Draw the waveform WHITE from the array
    for (int i = 1; i < size; ++i) {
        c_main.C.drawLine(i - 1, arr[i - 1], i, arr[i], WHITE);
    }

    //Erease and print the ball
    int temp_pos = parentState->m_position;
    c_main.C.fillCircle(15, m_lastBallPos, 8, BLACK);

    c_main.C.fillCircle(15, temp_pos, 8, GREEN);
    m_lastBallPos = temp_pos;
        

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

bool MicGameUI::isWaveformInCircle(int circleX, int circleY, int radius) {
    // Calculate the square of the radius to use in comparisons, to avoid computing square roots.
    int radiusSquared = radius * radius;

    // Check only the relevant part of the waveform
    for (int i = 14; i <= 30; ++i) {
        // Calculate the square of the distance from the point to the circle's center
        int dx = i - circleX;
        int dy = arr[i] - circleY;
        int distanceSquared = dx * dx + dy * dy;

        // If the distance squared is less than or equal to the radius squared, the point is inside the circle
        if (distanceSquared <= radiusSquared) {
            return true;  // Return true immediately upon finding any point inside the circle
        }
    }

    return false;  // If no points are inside the circle, return false
}
