#include "gyroscopeGame.h"
#include "gyroScopeGameUi.h"

GyroScopeGameUi::GyroScopeGameUi(GyroscopeGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
}

void GyroScopeGameUi::drawScoreAndTime() {
    // Draw score counter
    Serial.println("Draw screen time and score");
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
    Serial.println("Draw screen 1");
 //   c_main.C.fillScreen(BLACK); // Clear screen
    drawScoreAndTime();
    drawPlayerBall();
}

void GyroScopeGameUi::drawFallingBalls(int x, int y,uint16_t color) {
    c_main.C.fillCircle(x, y, parentState->m_fallingBallRadius, color);
}

void GyroScopeGameUi::drawPlayerBall() {
    Serial.println("Draw screen playerball");
    c_main.C.fillCircle(parentState->m_playerBallX, parentState->m_playerBally, parentState->PLAYERBALL_RADIUS, 0x07E0);

}

void GyroScopeGameUi::drawGameOver() {
    c_main.C.fillScreen(BLACK);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(10, 60);
    c_main.C.print("Score: ");
    c_main.C.print(parentState->m_score);
}
