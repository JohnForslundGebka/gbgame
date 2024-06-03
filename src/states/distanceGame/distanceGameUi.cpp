#include "distanceGameUi.h"
#include "distanceGame.h"


DistanceGameUi::DistanceGameUi(DistanceGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {}

void DistanceGameUi::init() {}

void DistanceGameUi::drawScreen1() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(17, 3);
    c_main.C.print("Distance");

    c_main.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    c_main.C.setTextColor(0x57FF);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(-1, 25);
    c_main.C.print("Hold device");

    c_main.C.setTextColor(0xFAAA);
    c_main.C.setTextSize(3);
    c_main.C.setCursor(22, 43);
    c_main.C.print(parentState->m_targetLength);

    c_main.C.setTextColor(0xFAAA);
    c_main.C.setTextSize(3);
    c_main.C.setCursor(71, 43);
    c_main.C.print("cm");

    c_main.C.setTextColor(0x57FF);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(16, 71);
    c_main.C.print("from the");


    c_main.C.setCursor(41, 88);
    c_main.C.print("wall");

    c_main.C.setTextColor(parentState->textColor);
    c_main.C.setCursor(20, 107);
    c_main.C.print("press A!");
}

void DistanceGameUi::drawScreen2() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(17, 3);
    c_main.C.print("Distance");

    c_main.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    c_main.C.setTextColor(0x57FF);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(5, 25);
    c_main.C.print("Your guess");

    c_main.C.setTextColor(GREEN);
    c_main.C.setTextSize(3);
    c_main.C.setCursor(22, 46);
    c_main.C.print(parentState->m_measured);

    c_main.C.setTextColor(GREEN);
    c_main.C.setTextSize(3);
    c_main.C.setCursor(71, 46);
    c_main.C.print("cm");

    c_main.C.setTextColor(0x57FF);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(16, 71);
    c_main.C.print("you were");

    c_main.C.setTextColor(RED);
    c_main.C.setCursor(53, 91);
    c_main.C.print(parentState->m_score);

    c_main.C.setTextColor(0xFFFF);
    c_main.C.setCursor(25, 109);
    c_main.C.print("cm off!");
}

void DistanceGameUi::drawScreen3(int score) {
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

void DistanceGameUi::drawScreen4() {
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

void DistanceGameUi::drawChallengeWinScreen(String &player1name, int player1score, String &player2name, int player2score) {
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

void DistanceGameUi::drawChallengeLooseScreen(String &player1name, int player1score, String &player2name, int player2score) {
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
