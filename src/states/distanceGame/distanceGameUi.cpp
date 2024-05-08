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

void DistanceGameUi::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(17, 3);
    c_main.C.print("Exiting...");
}
