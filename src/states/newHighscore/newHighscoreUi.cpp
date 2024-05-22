#include "newHighscoreUi.h"

NewHighscoreUi::NewHighscoreUi(NewHighscore *parentState) : parentState(parentState),
c_text(128,128,0,0),
c_dancingMan(24,24,53,90)
{}

void NewHighscoreUi::drawDance(int pose) {

    c_dancingMan.C.fillScreen(BLACK);
    c_dancingMan.C.drawCircle(64, 10, 5, WHITE); // Head
    c_dancingMan.C.drawLine(64, 15, 64, 35, WHITE); // Body

    // Dynamic arms and legs depending on the pose number
    switch (pose) {
        case 0: // Pose 1
            c_dancingMan.C.drawLine(64, 20, 50, 25, WHITE); // Left arm
            c_dancingMan.C.drawLine(64, 20, 78, 25, WHITE); // Right arm
            c_dancingMan.C.drawLine(64, 35, 50, 50, WHITE); // Left leg
            c_dancingMan.C.drawLine(64, 35, 78, 50, WHITE); // Right leg
            break;
        case 1: // Pose 2
            c_dancingMan.C.drawLine(64, 20, 54, 10, WHITE); // Left arm up
            c_dancingMan.C.drawLine(64, 20, 74, 10, WHITE); // Right arm up
            c_dancingMan.C.drawLine(64, 35, 58, 50, WHITE); // Left leg
            c_dancingMan.C.drawLine(64, 35, 70, 50, WHITE); // Right leg
            break;
        case 2: // Pose 3
            c_dancingMan.C.drawLine(64, 20, 50, 15, WHITE); // Left arm up further
            c_dancingMan.C.drawLine(64, 20, 78, 30, WHITE); // Right arm down
            c_dancingMan.C.drawLine(64, 35, 56, 55, WHITE); // Left leg bent
            c_dancingMan.C.drawLine(64, 35, 72, 55, WHITE); // Right leg bent
            break;
        case 3: // Pose 4
            c_dancingMan.C.drawLine(64, 20, 50, 30, WHITE); // Left arm down
            c_dancingMan.C.drawLine(64, 20, 78, 15, WHITE); // Right arm up further
            c_dancingMan.C.drawLine(64, 35, 50, 50, WHITE); // Left leg
            c_dancingMan.C.drawLine(64, 35, 78, 50, WHITE); // Right leg straight
            break;
    }
}

void NewHighscoreUi::drawText(int score) {
    c_text.C.setTextColor(0xFFFF);
    c_text.C.setTextSize(2);
    c_text.C.setTextWrap(false);
    c_text.C.setCursor(49, 27);
    c_text.C.print("NEW");
    c_text.C.setCursor(14, 49);
    c_text.C.print("HIGHSCORE");
    c_text.C.drawBitmap(2, 117, image_Background_bits, 128, 11, 0xFFFF);
    c_text.C.drawBitmap(34, 68, image_Space_bits, 65, 18, 0xA800);
    c_text.C.drawBitmap(-1, 1, image_Background_1_bits, 128, 11, 0xFFFF);
    c_text.C.drawBitmap(12, 27, image_FaceCharging_bits, 29, 14, 0xFFEA);
    c_text.C.setCursor(47, 69);
    c_text.C.print("123");
    c_text.C.drawBitmap(96, 25, image_Smile_bits, 18, 18, 0x555);
}
