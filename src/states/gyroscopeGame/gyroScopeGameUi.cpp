#include "gyroScopeGameUi.h"
#include "gyroscopeGame.h"

GyroScopeGameUi::GyroScopeGameUi(GyroscopeGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {

}

void GyroScopeGameUi::drawScoreAndTime() {
    // Draw score counter
    c_main.C.setTextSize(1);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setCursor(5, 5);
    c_main.C.print("");
    c_main.C.print(parentState->m_score);

    // Draw remaining time
    c_main.C.setCursor(90, 5);
    c_main.C.setTextColor((parentState->m_timeCounter < 10) ? 0xF800 : 0xFFFF); // Change color to red if remaining time is less than 10 seconds
    c_main.C.print(":");
    c_main.C.print(parentState->m_timeCounter); // Seconds

}

void GyroScopeGameUi::draw() {
    c_main.C.fillScreen(BLACK); // Clear screen
    drawScoreAndTime();
    drawFallingBalls();
    drawPlayerBall();
}

void GyroScopeGameUi::drawFallingBalls() {
    for(int i = 0; i < parentState->m_numFallingBalls; i++){
        c_main.C.fillCircle(parentState->m_fallingBallX[i], parentState->m_fallingBallY[i], parentState->m_fallingBallRadius, parentState->m_fallingBallColors[i]);
    }

}

void GyroScopeGameUi::drawPlayerBall() {
    c_main.C.fillCircle(parentState->m_playerBallX, parentState->m_playerBally, parentState->PLAYERBALL_RADIUS, 0x07E0);

}
