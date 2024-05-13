#include "mainMenuUi.h"
#include "states/globalStates.h"

MainMenuUi::MainMenuUi() : c_hand(16,11,7,30), c_text(128,128,0,0) {}

void MainMenuUi::init() {

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-GbgGame-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xFFEA);

    c_canvas.C.setTextColor(0xA800);
    c_canvas.C.setCursor(20, 62);
    c_canvas.C.print("123456789");

    c_canvas.C.drawBitmap(2, 64, image_hand_notice_bits, 16, 11, 0x555);

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(41, 88);
    c_canvas.C.print("Stringnb3");
    c_canvas.C.setCursor(41, 48);
    c_canvas.C.print("Stringnb1");
    c_canvas.C.setCursor(41, 33);
    c_canvas.C.print("Stringnb0");
    c_canvas.C.setCursor(41, 105);
    c_canvas.C.print("Stringnb4");
}

void MainMenuUi::moveUp() {
    c_hand.C.drawBitmap(0, 0, image_hand_notice_bits, 16, 11, 0x555);
}

void MainMenuUi::moveDown() {
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
