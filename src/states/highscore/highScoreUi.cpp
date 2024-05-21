#include "highScoreUi.h"

void HighScoreUi::init() {

    c_main.C.drawLine(0, 19, 128, 19, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(12, 3);
    c_main.C.print("HIGHSCORE");
    c_main.C.setTextColor(0x57FF);
    c_main.C.setCursor(20, 21);
    c_main.C.print("Measury");
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(1);
    c_main.C.setCursor(27, 37);
    c_main.C.print("Name");
    c_main.C.drawBitmap(106, 23, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_main.C.setCursor(90, 38);
    c_main.C.print("Score");
    c_main.C.drawBitmap(1, 21, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_main.C.setTextColor(0xFFEA);
    c_main.C.setTextSize(2);
    c_main.C.setCursor(3, 63);
    c_main.C.print("2");
    c_main.C.setCursor(3, 45);
    c_main.C.print("1");
    c_main.C.setCursor(3, 80);
    c_main.C.print("3");
    c_main.C.setCursor(3, 97);
    c_main.C.print("4");
    c_main.C.setCursor(3, 113);
    c_main.C.print("5");
    c_main.C.setTextColor(0xAD55);
    c_main.C.setCursor(19, 63);
    c_main.C.print("Melk");
    c_main.C.setTextColor(0xA815);
    c_main.C.setCursor(19, 45);
    c_main.C.print("Melk");
    c_main.C.setTextColor(0xAD55);
    c_main.C.setCursor(19, 80);
    c_main.C.print("Melk");
    c_main.C.setCursor(19, 96);
    c_main.C.print("Melk");
    c_main.C.setCursor(19, 112);
    c_main.C.print("Melk");
    c_main.C.setTextColor(0x540);
    c_main.C.setCursor(87, 63);
    c_main.C.print("200");
    c_main.C.setCursor(88, 47);
    c_main.C.print("200");
    c_main.C.setCursor(87, 80);
    c_main.C.print("200");
    c_main.C.setCursor(87, 96);
    c_main.C.print("200");
    c_main.C.setCursor(87, 111);
    c_main.C.print("200");
    c_main.C.drawRect(1, 95, 14, 17, 0xFFFF);
    c_main.C.drawRect(1, 111, 14, 17, 0xFFFF);
    c_main.C.drawRect(1, 78, 14, 17, 0xFFFF);
    c_main.C.drawRect(1, 61, 14, 17, 0xFFFF);
    c_main.C.drawRect(1, 44, 14, 17, 0xFFFF);

}

