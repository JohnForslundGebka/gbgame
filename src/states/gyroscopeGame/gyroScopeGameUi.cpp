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
    c_main.C.fillScreen(BLACK); // Clear screen
    drawScoreAndTime();
    drawPlayerBall();
}

void GyroScopeGameUi::drawFallingBalls(int x, int y,uint16_t color) {
    Serial.println("Draw screen fallingball");
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

void GyroScopeGameUi::drawCheckingSCore() {
    c_main.C.fillScreen(BLACK);
    c_main.C.drawBitmap(44, 47, image_Restoring_bits, 38, 32, 0xFFFF);
    c_main.C.drawBitmap(92, 20, image_cloud_upload_2_bits, 17, 16, 0xFFFF);
    c_main.C.drawBitmap(16, 20, image_envelope_bits, 17, 16, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(1);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(28, 89);
    c_main.C.print("Checking score");
    c_main.C.drawBitmap(56, 20, image_hour_glass_75_bits, 11, 16, 0xFFFF);
}

void GyroScopeGameUi::drawChallengeLoseScreen(String &player1name, int player1score, String &player2name, int player2score) {
    c_main.C.fillScreen(BLACK);
    c_main.C.setTextColor(0xFABF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(9, 38);
    c_main.C.print(player1name);
    c_main.C.setTextColor(0x57FF);
    c_main.C.setCursor(14, 10);
    c_main.C.print("YOU LOST");
    c_main.C.setTextColor(0xFABF);
    c_main.C.setCursor(8, 56);
    c_main.C.print(player2name);
    c_main.C.setTextColor(0x540);
    c_main.C.setCursor(78, 57);
    c_main.C.print(player2score);
    c_main.C.setCursor(77, 38);
    c_main.C.print(player1score);
    c_main.C.drawLine(59, 64, 71, 64, 0xFFFF);
    c_main.C.drawLine(59, 46, 71, 46, 0xFFFF);
    c_main.C.drawBitmap(34, 75, image_Cry_dolph_bits, 55, 52, 0xFFFF);
}

void GyroScopeGameUi::drawChallengeWinScreen(String &player1name, int player1score, String &player2name, int player2score) {
    c_main.C.fillScreen(BLACK);
    c_main.C.setTextColor(0xFABF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(9, 38);
    c_main.C.print(player1name);
    c_main.C.setTextColor(0x57FF);
    c_main.C.setCursor(16, 9);
    c_main.C.print("YOU WON!");
    c_main.C.setTextColor(0xFABF);
    c_main.C.setCursor(8, 56);
    c_main.C.print(player2name);
    c_main.C.setTextColor(0x540);
    c_main.C.setCursor(78, 57);
    c_main.C.print(player2score);
    c_main.C.setCursor(77, 38);
    c_main.C.print(player1score);
    c_main.C.drawLine(59, 64, 71, 64, 0xFFFF);
    c_main.C.drawLine(59, 46, 71, 46, 0xFFFF);
    c_main.C.drawBitmap(31, 85, image_Connected_bits, 62, 31, 0xFFFF);
}

void GyroScopeGameUi::drawNoHighcoreScreen(int score) {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.drawBitmap(36, 74, image_Cry_dolph_bits, 55, 52, 0x555);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(11, 38);
    c_main.C.print("Highscore");
    c_main.C.setTextColor(0xA800);
    c_main.C.setCursor(51, 23);
    c_main.C.print("No");
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setCursor(10, 57);
    c_main.C.print("This Time");
    c_main.C.setCursor(23, 5);
    c_main.C.print(score);
    c_main.C.setTextSize(1);
    c_main.C.setCursor(63, 12);
    c_main.C.print("Points");
}
