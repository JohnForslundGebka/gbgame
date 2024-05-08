#include "mainMenuUi.h"

MainMenuUi::MainMenuUi() : c_hand(16,11,7,30), c_text(128,128,0,0) {}

void MainMenuUi::init() {
   drawHand();
   drawText();
}

void MainMenuUi::drawHand() {
    c_hand.C.drawBitmap(0, 0, image_hand_notice_bits, 16, 11, 0x555);
}

void MainMenuUi::drawText() {
    c_text.C.setTextColor(0xFFFF);
    c_text.C.setTextSize(2);
    c_text.C.setTextWrap(false);
    c_text.C.setCursor(18, 0);
    c_text.C.print("-GbgGame-");
    c_text.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_text.C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xA800);
    c_text.C.setCursor(31, 26);
    c_text.C.print("Games");
    c_text.C.setCursor(31, 47);
    c_text.C.print("Settings");
}
